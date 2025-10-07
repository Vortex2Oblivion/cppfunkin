#include "playfield.hpp"
#include "strumnote.hpp"
#include "../engine/group.hpp"
#include <iostream>

bool noteDataSorter(funkin::NoteData a, funkin::NoteData b)
{
    return a.time < b.time;
}

funkin::PlayField::PlayField(std::vector<NoteData> noteDatas)
{
    setup(noteDatas);
}

funkin::PlayField::PlayField(std::vector<NoteData> noteDatas, std::vector<Character *> characters)
{
    this->characters = characters;
    setup(noteDatas);
}

funkin::PlayField::~PlayField()
{
}

void funkin::PlayField::setup(std::vector<NoteData> noteDatas)
{

    strums = new engine::Group<funkin::StrumNote>();
    notes = new engine::Group<funkin::Note>();
    this->noteDatas = noteDatas;
    std::sort(noteDatas.begin(), noteDatas.end(), noteDataSorter);
    add(strums);
    add(notes);
    generateStaticArrows(true);
}

void funkin::PlayField::update(float delta)
{
    engine::Group<Object>::update(delta);
    while (noteDataIndex < noteDatas.size() && conductor->time >= noteDatas[noteDataIndex].time - 1.0)
    {
        NoteData data = noteDatas[noteDataIndex];
        Note *note = new Note(data.time * 1000.0f, data.lane, scrollSpeed, strums->members[data.lane]);
        note->isPlayer = data.isPlayer;
        notes->add(note);
        noteDataIndex++;
    }

    std::vector<funkin::Note *> toInvalidate;
    for (auto note : notes->members)
    {
        if (!note->alive)
        {
            continue;
        }

        if (conductor->time * 1000.0 > note->strumTime + 180.0)
        {
            note->alive = false;
            toInvalidate.push_back(note);
            misses++;
        }
        else
        {
            note->songPos = conductor->time;
        }
    }

    // inputs
    // thanks for helping my dumbass with this rudy
    float closestDistance = INFINITY;

    pressedArray = {IsKeyDown(KEY_D), IsKeyDown(KEY_F), IsKeyDown(KEY_J), IsKeyDown(KEY_K)};
    justHitArray = {IsKeyPressed(KEY_D), IsKeyPressed(KEY_F), IsKeyPressed(KEY_J), IsKeyPressed(KEY_K)};

    if (!cpuControlled)
    {
        for (size_t lane = 0; lane < justHitArray.size(); lane++)
        {
            if (justHitArray[lane])
            {
                strums->members[lane]->playAnimation("press");
                strums->members[lane]->offset = strums->members[lane]->offset.Scale(0.0f);
            }
        }
    }

    for (auto note : notes->members)
    {
        if (note == nullptr || !note->alive)
        {
            continue;
        }
        bool hittable = false;
        float minHitTime = 180.0f;
        float maxHitTime = 180.0f;

        if (cpuControlled)
        {
            minHitTime = 0;
        }

        if (note->strumTime < (conductor->time * 1000 + minHitTime) && note->strumTime > (conductor->time * 1000 - maxHitTime))
        {
            hittable = true;
        }

        if (!hittable || (!justHitArray[note->lane] && !cpuControlled))
        {
            continue;
        }

        float rawHitTime = note->strumTime - conductor->time * 1000.f;
        float distance = abs(rawHitTime);

        if (distance >= closestDistance)
        {
            continue;
        }

        closestDistance = distance;

        int lane = note->lane;

        for (auto character : characters)
        {
            character->playAnimation(singAnimArray[lane]);
        }
        int addScore = (int)abs(500.0f - (note->strumTime - conductor->time) / 1000.0f);
        score += addScore;
        strums->members[lane]->playAnimation("confirm");
        strums->members[lane]->offset.x = -30;
        strums->members[lane]->offset.y = -30;
        note->alive = false;
        toInvalidate.push_back(note);
    }

    for (size_t i = 0; i < toInvalidate.size(); i++)
    {
        invalidateNote(toInvalidate[i]);
    }

    for (auto strum : strums->members)
    {
        if (!cpuControlled)
        {
            if (!pressedArray[strum->lane])
            {
                strum->playAnimation("static");
                strum->offset.x = strum->offset.y = 0.0;
            }
        }
        else
        {
            if (strum->currentAnimation->currentFrame >= strum->currentAnimation->frames.size() - 1)
            {
                strum->playAnimation("static");
                strum->offset.x = strum->offset.y = 0.0;
            }
        }
    }
}

void funkin::PlayField::invalidateNote(funkin::Note *note)
{
    note->alive = false;
    notes->remove(note);
}

void funkin::PlayField::generateStaticArrows(bool player)
{
    for (int i = 0; i < 4; i++)
    {
        StrumNote *babyArrow = new StrumNote(42, 50, i, player);
        babyArrow->setPosition();
        strums->add(babyArrow);
    }
}
