#include "playfield.hpp"

#include <algorithm>
#include <cmath>
#include <utility>
#include <raylib-cpp.hpp>

#include "../engine/group.hpp"
#include "strumnote.hpp"

bool noteDataSorter(const funkin::NoteData a, const funkin::NoteData b) { return a.time < b.time; }

funkin::PlayField::PlayField(const float x, const float y, std::vector<NoteData> noteDatas, std::vector<Character*> characters, const bool cpuControlled) {
    this->position.x = x;
    this->position.y = y;
    this->characters = std::move(characters);
    this->cpuControlled = cpuControlled;
    this->noteDatas = std::move(noteDatas);

    strums = new engine::Group<funkin::StrumNote>();
    notes = new engine::Group<funkin::Note>();

    std::sort(this->noteDatas.begin(), this->noteDatas.end(), noteDataSorter);

    add(strums);
    add(notes);

    generateStaticArrows(cpuControlled);
}

funkin::PlayField::~PlayField() = default;

void funkin::PlayField::update(const float delta) {
    engine::Group<Object>::update(delta);
    while (!noteDatas.empty() && noteDataIndex < noteDatas.size() && ceilf(conductor->time) >= floorf(noteDatas[noteDataIndex].time - 2.0f)) {
        const auto data = noteDatas[noteDataIndex];
        const auto note = new Note(data.time * 1000.0f, data.lane, scrollSpeed);
        const float positionX = strums->members[data.lane]->position.x;

        note->position.x = positionX;
        note->isPlayer = data.isPlayer;

        lastSpawnedNotes[data.lane] = note;

        const auto roundSustainLength = static_cast<size_t>(roundf(data.sustainLength / conductor->getStepCrochet()));

        if (roundSustainLength > 0) {
            for (size_t i = 0; i < roundSustainLength; i++) {
                const auto sustainNote = new Note(data.time * 1000.0f + (conductor->getStepCrochet() * i * 1000.0f), data.lane, scrollSpeed);
                sustainNote->isPlayer = data.isPlayer;
                sustainNote->playAnimation("hold");
                sustainNote->isSustain = true;
                sustainNote->scale.y = conductor->getStepCrochet() * 1000.0f * 0.45f * scrollSpeed / 44.0f;
                sustainNote->originFactor = raylib::Vector2::Zero();
                sustainNote->position.x = positionX + 51.0f / 1.5f;
                sustainNote->parentNote = lastSpawnedNotes[data.lane];
                lastSpawnedNotes[data.lane] = sustainNote;

                if (i == roundSustainLength - 1) {
                    sustainNote->playAnimation("hold_end");
                    sustainNote->scale.y = 0.7f;
                }

                notes->add(sustainNote);
            }
        }

        notes->add(note);
        noteDataIndex++;

    }

    // inputs
    // thanks for helping my dumbass with this rudy
    float closestDistances[4] = {INFINITY, INFINITY, INFINITY, INFINITY};

    if (!cpuControlled) {
        pressedArray = {IsKeyDown(KEY_D), IsKeyDown(KEY_F), IsKeyDown(KEY_J), IsKeyDown(KEY_K)};
        justHitArray = {IsKeyPressed(KEY_D), IsKeyPressed(KEY_F), IsKeyPressed(KEY_J), IsKeyPressed(KEY_K)};
        for (size_t lane = 0; lane < justHitArray.size(); lane++) {
            if (!justHitArray[lane]) {
                continue;
            }
            funkin::StrumNote* strum = strums->members[lane];
            strum->playAnimation("press");
            strum->offset = strum->offset.Scale(0.0f);
        }
    }

    for (auto note : notes->members) {
        if (note == nullptr || !note->alive || note->wasMissed) {
            continue;
        }

        const float hitWindow = conductor->time * 1000.0f;

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

        const float actualMinHitTime = cpuControlled ? 0 : minHitTime;

        const float minHitWindow = (hitWindow + actualMinHitTime);
        const float maxHitWindow = (hitWindow - maxHitTime);

        const bool hittable = note->strumTime <= minHitWindow && note->strumTime >= maxHitWindow;


        // if statement of DOOM
        // crashes if I separate into variables, so maybe figure out what's going on there?

        const bool wasKeyPressed = justHitArray[lane] || cpuControlled;

        if (!hittable || (!wasKeyPressed && !(note->isSustain && pressedArray[lane] && (note->parentNote->wasHit || (!note->parentNote->alive && !note->parentNote->wasMissed))))) {
            continue;
        }

        const float rawHitTime = note->strumTime - conductor->time * 1000.f;
        const float distance = rawHitTime;

        // 5ms allowed or smth idk
        float& closestDistance = closestDistances[lane];

        if (closestDistance != INFINITY && abs(closestDistance - distance) > 5.0f) {
            continue;
        }

        closestDistance = distance;

        for (const auto character : characters) {
            character->playAnimation(singAnimArray[lane]);
        }

        const float addScore = abs(500.0f - (note->strumTime - conductor->time) / 1000.0f);

        score += static_cast<int>(addScore);
        health = Clamp(health + (addScore / 200.0f), 0, 100);

        funkin::StrumNote* strum = strums->members[lane];
        strum->playAnimation("confirm");
        strum->offset.x = -30;
        strum->offset.y = -30;

        note->wasHit = true;
        toInvalidate.push_back(note);
    }

    for (const auto note : toInvalidate) {
        invalidateNote(note);
    }

    toInvalidate.clear();

    for (const auto strum : strums->members) {
        const engine::Animation* animation = strum->currentAnimation;

        bool playStaticAnimation = cpuControlled ? animation->currentFrame >= animation->frames.size() - 1 : !pressedArray[strum->lane];

        if (!playStaticAnimation) {
            continue;
        }

        strum->playAnimation("static");
        strum->offset.x = strum->offset.y = 0.0;
    }
}

void funkin::PlayField::invalidateNote(funkin::Note* note) const {
    if (!note->alive) {
        return;
    }
    notes->remove(note);
    delete note;
}

void funkin::PlayField::generateStaticArrows(const bool player) const {
    for (int i = 0; i < 4; i++) {
        auto* babyArrow = new StrumNote(42, 50, i, player);
        babyArrow->setPosition();
        strums->add(babyArrow);
    }
}

void funkin::PlayField::calculateAccuracy() { accuracy = 100.0f * (static_cast<float>(noteDatas.size()) / (noteDatas.size() + misses)); }
