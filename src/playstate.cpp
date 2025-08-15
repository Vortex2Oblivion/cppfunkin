#include "playstate.hpp"
#include "note.hpp"
#include "strumnote.hpp"
#include "sparrowsprite.hpp"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include "game.hpp"

funkin::PlayState::PlayState(std::string song, std::string difficulty)
{
    camHUD = new raylib::Camera2D(raylib::Vector2(0, 0), raylib::Vector2(0, 0), 0.0f, 1.0f);
    funkin::Game::cameras.push_back(camHUD);

    funkin::Game::defaultCamera->zoom = 0.45f;

    dad = new Character(0, 0);
    dad->loadGraphic("assets/images/defected.png", "assets/images/defected.xml");
    dad->addAnimationByPrefix("idle", "defected idle", 24);
    dad->playAnimation("idle");
    add(dad);

    loadSong(song, difficulty);
}

funkin::PlayState::~PlayState()
{
}

void funkin::PlayState::loadSong(std::string song, std::string difficulty)
{
    std::string basePath = "assets/songs/" + song + "/";
    std::ifstream chartFile(basePath + difficulty + ".json");
    nlohmann::json parsedChart = nlohmann::json::parse(chartFile);
    tracks.push_back(new raylib::Music(basePath + "Inst.ogg"));
    tracks.push_back(new raylib::Music(basePath + "Voices.ogg"));

    generateStaticArrows(false);
    generateStaticArrows(true);
    for (auto sectionNotes : parsedChart["song"]["notes"])
    {
        for (auto sectionNote : sectionNotes["sectionNotes"])
        {
            bool playerNote = (sectionNote[1] < 4) ? (bool)(sectionNotes["mustHitSection"]) : (!sectionNotes["mustHitSection"]);
            int lane = ((int)sectionNote[1] % 4) + (playerNote ? 0 : 4);
            Note *note = new Note(sectionNote[0], lane % 4, parsedChart["song"]["speed"], strumLineNotes[lane]);
            note->camera = camHUD;
            note->isPlayer = playerNote;
            notes.push_back(note);
            add(note);
        }
    }
    _conductor = new Conductor(tracks);
    tracks[0]->Play();
    tracks[1]->Play();
}

void funkin::PlayState::update(double delta)
{
    State::update(delta);
    _conductor->update(delta);

    if (IsKeyPressed(KEY_SPACE))
    {
        dad->playAnimation("idle");
    }
    for (auto note : notes)
    {
        if (!note->alive)
        {
            continue;
        }
        note->songPos = _conductor->time;
    }

    // inputs
    // thanks for helping my dumbass with this rudy
    float closestDistance = INFINITY;

    std::vector<Note *> notesToDelete = {};
    justHitArray = {IsKeyPressed(KEY_D), IsKeyPressed(KEY_F), IsKeyPressed(KEY_J), IsKeyPressed(KEY_K)};
    for (auto note : notes)
    {
        if (note == nullptr || !note->alive)
        {
            continue;
        }
        bool hittable = false;
        float minHitTime = 180.0f;
        float maxHitTime = 180.0f;

        if (!note->isPlayer)
        {
            minHitTime = 0;
        }
        if (note->strumTime < (_conductor->time * 1000 + minHitTime) && note->strumTime > (_conductor->time * 1000 - maxHitTime))
        {
            hittable = true;
        }
        if (!hittable || (!justHitArray[note->lane] && note->isPlayer))
        {
            continue;
        }
        double rawHitTime = note->strumTime - _conductor->time * 1000;
        double distance = abs(rawHitTime);
        if (distance < closestDistance)
        {
            closestDistance = distance;
        }
        else
        {
            continue;
        }
        int lane = note->lane;
        if (!note->isPlayer)
        {
            lane += 4;
        }
        strumLineNotes[lane]->playAnimation("confirm");
        strumLineNotes[lane]->offset.x = -30;
        strumLineNotes[lane]->offset.y = -30;
        notesToDelete.push_back(note);
    }
    for (auto note : notesToDelete)
    {
        notes.erase(find(notes.begin(), notes.end(), note));
        remove(note);
    }
    for (auto track : tracks)
    {
        track->Update();
    }

    for (auto strum : strumLineNotes)
    {
        if (strum->currentAnimation->currentFrame >= strum->currentAnimation->frames.size() - 1)
        {
            strum->playAnimation("static");
            strum->offset.x = strum->offset.y = 0.0;
        }
    }
}

void funkin::PlayState::generateStaticArrows(bool player)
{
    for (int i = 0; i < 4; i++)
    {
        StrumNote *babyArrow = new StrumNote(42, 50, i, player);
        babyArrow->setPosition();
        babyArrow->camera = camHUD;
        strumLineNotes.push_back(babyArrow);
        add(babyArrow);
    }
}