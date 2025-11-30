#include "playfield.hpp"

#include <algorithm>
#include <cmath>
#include <utility>
#include <raylib-cpp.hpp>

#include "../engine/group.hpp"
#include "strumnote.hpp"

bool noteDataSorter(const funkin::NoteData a, const funkin::NoteData b) { return a.time < b.time; }

funkin::PlayField::PlayField(const float x, const float y, std::vector<NoteData> noteDatas, std::vector<std::shared_ptr<funkin::Character>> characters, const bool cpuControlled) {
    this->position.x = x;
    this->position.y = y;
    this->characters = std::move(characters);
    this->cpuControlled = cpuControlled;
    this->noteDatas = std::move(noteDatas);

    strums = std::make_shared<engine::Group<funkin::StrumNote>>();
    notes = std::make_shared<engine::Group<funkin::Note>>();

    std::ranges::sort(this->noteDatas, noteDataSorter);

    add(strums);
    add(notes);

    generateStaticArrows(cpuControlled);
}

funkin::PlayField::~PlayField(){
    this->noteDatas.clear();
};

void funkin::PlayField::update(const float delta) {
    engine::Group<Object>::update(delta);
    while (!noteDatas.empty() && noteDataIndex < noteDatas.size() && ceilf(conductor->time) >= floorf(noteDatas[noteDataIndex].time - 2000.0f)) {
        const auto [time, lane, isPlayer, sustainLength] = noteDatas[noteDataIndex];
        const auto note = std::make_shared<funkin::Note>(time, lane, scrollSpeed);
        const float positionX = strums->members[lane]->position.x;

        note->position.x = positionX;
        note->isPlayer = isPlayer;

        lastSpawnedNotes[lane] = note;

        if (const auto roundSustainLength = static_cast<size_t>(roundf(sustainLength / conductor->getStepCrochet())); roundSustainLength > 0) {
            for (size_t i = 0; i < roundSustainLength; i++) {
                const auto sustainNote = std::make_shared<funkin::Note>(time + (conductor->getStepCrochet() * static_cast<float>(i)), lane, scrollSpeed);
                sustainNote->isPlayer = isPlayer;
                sustainNote->playAnimation("hold");
                sustainNote->isSustain = true;
                sustainNote->scale.y = conductor->getStepCrochet() * 0.45f * scrollSpeed / sustainNote->getFrameSize().y;
                sustainNote->originFactor = raylib::Vector2(0.5, 0.0);
                sustainNote->parentNote = lastSpawnedNotes[lane];
                lastSpawnedNotes[lane] = sustainNote;

                if (i == roundSustainLength - 1) {
                    sustainNote->playAnimation("hold_end");
                    sustainNote->scale.y = 0.7f;
                }

                sustainNote->position.x = positionX + (note->getFrameSize().x - sustainNote->getFrameSize().x) / 2.0f - 4.0f;
                notes->add(sustainNote);
            }
        }

        notes->add(note);
        noteDataIndex++;

    }

    // inputs
    // thanks for helping my dumbass with this rudy
    std::array<float, 4> closestDistances = {INFINITY, INFINITY, INFINITY, INFINITY};

    if (!cpuControlled) {
        pressedArray = {IsKeyDown(KEY_D), IsKeyDown(KEY_F), IsKeyDown(KEY_J), IsKeyDown(KEY_K)};
        justHitArray = {IsKeyPressed(KEY_D), IsKeyPressed(KEY_F), IsKeyPressed(KEY_J), IsKeyPressed(KEY_K)};
        for (size_t lane = 0; lane < justHitArray.size(); lane++) {
            if (!justHitArray[lane]) {
                continue;
            }
            const auto strum = strums->members[lane];
            strum->playAnimation("press");
            strum->centerOffsets();
        }
    } else {
        for (bool & i : pressedArray) {
            i = true;
        }
    }

    for (const auto& note : notes->members) {
        if (note == nullptr || !note->alive || note->wasMissed) {
            continue;
        }

        note->laneHeld = pressedArray[note->lane];

        if (note->isSustain && note->wasHit) {
            if (conductor->time > note->strumTime + maxHitTime) {
               toInvalidate.push_back(note);
            }

            note->updateY(conductor->time);
            continue;
        }

        const float hitWindow = conductor->time;

        if (hitWindow > note->strumTime + maxHitTime && !cpuControlled) {
            note->wasMissed = true;
            toInvalidate.push_back(note);
            misses++;
            health = Clamp(health - 5.0f, 0, 100);
            calculateAccuracy();
            continue;
        }

        note->updateY(conductor->time);

        const int lane = note->lane;
        const auto strum = strums->members[lane];

        const float minHitWindow = (hitWindow + maxHitTime);
        const float maxHitWindow = (hitWindow - maxHitTime);

        const bool hittable = note->strumTime <= minHitWindow && note->strumTime >= maxHitWindow;

        if (!hittable) {
            continue;
        }

        if (cpuControlled && note->strumTime > conductor->time) {
            continue;
        }

        if (!cpuControlled) {
            if (note->isSustain && !pressedArray[lane] && !note->isQueuedSustain) {
                continue;
            } else if (!note->isSustain && !justHitArray[lane]) {
                continue;
            }

            if (pressedArray[lane] && note->isSustain && conductor->time < note->strumTime) {
                if (conductor->time + conductor->getStepCrochet() <= note->strumTime) {
                    note->isQueuedSustain = true;
                }

                continue;
            }

            if (!pressedArray[lane] && note->isQueuedSustain && conductor->time < note->strumTime) {
                continue;
            }
        }

        const float distance = note->strumTime - conductor->time;

        // 5ms allowed or smth idk
        float& closestDistance = closestDistances[lane];

        if (distance > closestDistance) {
            continue;
        }

        closestDistance = distance;

        for (const auto& character : characters) {
            character->playAnimation(singAnimArray[lane]);
        }

        float addScore = abs(500.0f - (note->strumTime - conductor->time));
        if (note->isSustain) {
            addScore = 10.0;
        }

        score += static_cast<int>(addScore);
        health = Clamp(health + (addScore / 200.0f), 0, 100);

        strum->playAnimation("confirm");
        strum->centerOffsets();

        note->wasHit = true;

        if (!note->isSustain) {
            toInvalidate.push_back(note);
        }
    }

    for (const auto& note : toInvalidate) {
        invalidateNote(note);
    }

    toInvalidate.clear();

    for (const auto& strum : strums->members) {
        const auto animation = strum->currentAnimation;
        bool playStaticAnimation = cpuControlled ? animation->currentFrame >= animation->frames.size() - 1 : !pressedArray[strum->lane];

        if (!playStaticAnimation) {
            continue;
        }

        strum->playAnimation("static");
        strum->updateHitbox();
        strum->centerOffsets();
    }
}

void funkin::PlayField::invalidateNote(
    const std::shared_ptr<funkin::Note> &note) const {
    if (!note->alive) {
        return;
    }
    notes->remove(note);
    //delete note;
}

void funkin::PlayField::generateStaticArrows(const bool player) const {
    for (int i = 0; i < 4; i++) {
        const auto babyArrow = std::make_shared<funkin::StrumNote>(42, 50, i, player);
        babyArrow->setPosition();
        strums->add(babyArrow);
    }
}

void funkin::PlayField::calculateAccuracy() { accuracy = 100.0f * (static_cast<float>(noteDatas.size()) / (noteDatas.size() + misses)); }
