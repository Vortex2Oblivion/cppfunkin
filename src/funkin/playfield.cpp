#include "playfield.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "../engine/group.hpp"
#include "strumnote.hpp"

// TODO: Fix double note hit bug.

bool noteDataSorter(funkin::NoteData a, funkin::NoteData b) { return a.time < b.time; }

funkin::PlayField::PlayField(float x, float y, std::vector<NoteData> noteDatas, std::vector<Character*> characters, bool cpuControlled) {
    this->position.x = x;
    this->position.y = y;
    this->characters = characters;
    this->cpuControlled = cpuControlled;
    this->noteDatas = noteDatas;
    strums = new engine::Group<funkin::StrumNote>();
    notes = new engine::Group<funkin::Note>();
    std::sort(this->noteDatas.begin(), this->noteDatas.end(), noteDataSorter);
    add(strums);
    add(notes);
    generateStaticArrows(cpuControlled);
}

funkin::PlayField::~PlayField() {}

void funkin::PlayField::update(float delta) {
    engine::Group<Object>::update(delta);
    while (noteDatas.size() > 0 && noteDataIndex < noteDatas.size() && ceilf(conductor->time) >= floorf(noteDatas[noteDataIndex].time - 2.0f)) {
        NoteData data = noteDatas[noteDataIndex];
        Note* note = new Note(data.time * 1000.0f, data.lane, scrollSpeed, strums->members[data.lane]);
        note->isPlayer = data.isPlayer;
        if(data.sustainLength > 0.0f){
            Note* sustainNote = new Note(data.time * 1000.0f, data.lane, scrollSpeed, strums->members[data.lane]);
            sustainNote->isPlayer = data.isPlayer;
            sustainNote->playAnimation("hold");
            sustainNote->scale.y = (data.sustainLength * 0.45 * scrollSpeed) * (60.0f / conductor->bpm * 44);
            sustainNote->isSustain = true;
            notes->add(sustainNote);
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
            if (justHitArray[lane]) {
                strums->members[lane]->playAnimation("press");
                strums->members[lane]->offset = strums->members[lane]->offset.Scale(0.0f);
            }
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
        }
        note->songPos = conductor->time;

        bool hittable = false;

        float actualMinHitTime = cpuControlled ? 0 : minHitTime;

        if (note->strumTime <= (hitWindow + actualMinHitTime) && note->strumTime >= (hitWindow - maxHitTime)) {
            hittable = true;
        }

        if (!hittable || (!justHitArray[note->lane] && !cpuControlled)) {
            continue;
        }

        float rawHitTime = note->strumTime - conductor->time * 1000.f;
        float distance = rawHitTime;

        // 5ms allowed or smth idk
        if (closestDistances[note->lane] != INFINITY && abs(closestDistances[note->lane] - distance) > 5.0f)
        {
            continue;
        }

        closestDistances[note->lane] = distance;

        int lane = note->lane;

        for (auto character : characters) {
            character->playAnimation(singAnimArray[lane]);
        }
        int addScore = (int)abs(500.0f - (note->strumTime - conductor->time) / 1000.0f);
        score += addScore;
        health = Clamp(health + (addScore / 200.0f), 0, 100);
        strums->members[lane]->playAnimation("confirm");
        strums->members[lane]->offset.x = -30;
        strums->members[lane]->offset.y = -30;
        toInvalidate.push_back(note);
    }

    for (auto note : toInvalidate) {
        invalidateNote(note);
    }

    toInvalidate.clear();

    for (auto strum : strums->members) {
        if (!cpuControlled) {
            if (!pressedArray[strum->lane]) {
                strum->playAnimation("static");
                strum->offset.x = strum->offset.y = 0.0;
            }
        } else {
            if (strum->currentAnimation->currentFrame >= strum->currentAnimation->frames.size() - 1) {
                strum->playAnimation("static");
                strum->offset.x = strum->offset.y = 0.0;
            }
        }
    }
}

void funkin::PlayField::invalidateNote(funkin::Note* note) {
    if (!note->alive || note == nullptr) {
        return;
    }
    notes->remove(note);
    delete note;
}

void funkin::PlayField::generateStaticArrows(bool player) {
    for (int i = 0; i < 4; i++) {
        StrumNote* babyArrow = new StrumNote(42, 50, i, player);
        babyArrow->setPosition();
        strums->add(babyArrow);
    }
}

void funkin::PlayField::calculateAccuracy() { accuracy = 100.0f * ((float)noteDatas.size() / (noteDatas.size() + misses)); }
