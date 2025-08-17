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

    funkin::Game::defaultCamera->zoom = 0.575f;

    Sprite *sky = new Sprite(-1250, -900);
    sky->loadGraphic("assets/images/Fsky.png");
    add(sky);

    Sprite *ground = new Sprite(-1600, -900);
    ground->loadGraphic("assets/images/ground.png");
    add(ground);

    Sprite *banner = new Sprite(-1600, -700);
    banner->loadGraphic("assets/images/sexcatch.png");
    add(banner);

    Sprite *beach = new Sprite(-1600, -900);
    beach->loadGraphic("assets/images/ggg.png");
    add(beach);

    dad = new Character(-550, 0, "defected");
    funkin::Game::defaultCamera->target = dad->position;
    funkin::Game::defaultCamera->target.x -= 500;
    funkin::Game::defaultCamera->target.y -= 250;
    add(dad);

    boyfriend = new Character(100, 250, "bf");
    add(boyfriend);

    loadSong(song, difficulty);
}

funkin::PlayState::~PlayState()
{
}

bool noteDataSorter(funkin::NoteData a, funkin::NoteData b)
{
    return a.time < b.time;
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

    scrollSpeed = parsedChart["song"]["speed"];

    for (auto sectionNotes : parsedChart["song"]["notes"])
    {
        for (auto sectionNote : sectionNotes["sectionNotes"])
        {
            bool playerNote = (sectionNote[1] < 4) ? (bool)(sectionNotes["mustHitSection"]) : (!sectionNotes["mustHitSection"]);
            int lane = ((int)sectionNote[1] % 4) + (playerNote ? 0 : 4);
            noteDatas.push_back(NoteData{
                double(sectionNote[0]) / 1000.0, // time
                lane % 4,                        // lane
                playerNote,                      // isPlayer
            });
        }
    }

    std::sort(noteDatas.begin(), noteDatas.end(), noteDataSorter);

    _conductor = new Conductor(tracks);
    tracks[0]->Play();
    tracks[1]->Play();
}

void funkin::PlayState::update(double delta)
{
    _conductor->update(delta);
    while (noteDataIndex < noteDatas.size() && _conductor->time > noteDatas[noteDataIndex].time - 1.0)
    {
        NoteData data = noteDatas[noteDataIndex];
        Note *note = new Note(data.time * 1000.0, data.lane, scrollSpeed, strumLineNotes[data.lane + (!data.isPlayer ? 4 : 0)]);
        note->camera = camHUD;
        note->isPlayer = data.isPlayer;
        notes.push_back(note);
        add(note);
        noteDataIndex++;
    }

    State::update(delta);

    if (IsKeyPressed(KEY_SPACE))
    {
        dad->playAnimation("idle");
    }

    std::vector<Note *> notesToDelete;
    for (auto note : notes)
    {
        if (!note->alive)
        {
            continue;
        }

        if (_conductor->time * 1000.0 > note->strumTime + 180.0)
        {
            notesToDelete.push_back(note);
            note->alive = false;
        }
        else
        {
            note->songPos = _conductor->time;
        }
    }

    // inputs
    // thanks for helping my dumbass with this rudy
    float closestDistance = INFINITY;

    justHitArray = {IsKeyPressed(KEY_D), IsKeyPressed(KEY_F), IsKeyPressed(KEY_J), IsKeyPressed(KEY_K)};
    std::vector<std::string> singAnimArray = {"singLEFT", "singDOWN", "singUP", "singRIGHT"};
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
            dad->playAnimation(singAnimArray[lane]);
            lane += 4;
        }
        else
        {
            boyfriend->playAnimation(singAnimArray[lane]);
        }
        strumLineNotes[lane]->playAnimation("confirm");
        strumLineNotes[lane]->centerOffsets();
        strumLineNotes[lane]->offset = strumLineNotes[lane]->offset.Scale(0.5f);
        // strumLineNotes[lane]->offset.x = -30;
        // strumLineNotes[lane]->offset.y = -30;
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