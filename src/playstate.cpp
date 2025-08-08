#include "playstate.hpp"
#include "note.hpp"
#include "strumnote.hpp"
#include "sparrowsprite.hpp"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

funkin::PlayState::PlayState()
{
    loadSong("parasitic", "hard");
    animatedNote = new SparrowSprite(0, 0);
    animatedNote->loadGraphic("assets/images/notes.png", "assets/images/notes.xml");
    animatedNote->addAnimationByPrefix("up confirm", "up confirm", 24);
    animatedNote->addAnimationByPrefix("down confirm", "down confirm", 24);
    animatedNote->addAnimationByPrefix("right confirm", "right confirm", 24);
    animatedNote->addAnimationByPrefix("left confirm", "left confirm", 24);
    animatedNote->scale.x = 0.7f;
    animatedNote->scale.y = 0.7f;

    animatedNote->playAnimation("up confirm");
    add(animatedNote);
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

    std::vector<raylib::Color> colors = {PURPLE, BLUE, GREEN, RED};
    generateStaticArrows(false);
    generateStaticArrows(true);
    for (auto _note : parsedChart["song"]["notes"])
    {
        for (auto sectionNote : _note["sectionNotes"])
        {
            bool playerNote = (sectionNote[1] < 4) ? (!_note["mustHitSection"]) : (bool)(_note["mustHitSection"]);
            int lane = ((int)sectionNote[1] % 4) + (playerNote ? 4 : 0);
            Note *__note = new Note(sectionNote[0], lane % 4, parsedChart["song"]["speed"], strumLineNotes[lane]);
            __note->loadGraphic("assets/images/slungus.png");
            __note->color = colors[(int)sectionNote[1] % 4];
            __note->isPlayer = !playerNote;
            notes.push_back(__note);
            add(__note);
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
    double closestDistance = INFINITY;

    std::vector<Note *> notesToDelete = {};
    justHitArray = {IsKeyPressed(KEY_D), IsKeyPressed(KEY_F), IsKeyPressed(KEY_J), IsKeyPressed(KEY_K)};
    for (auto note : notes)
    {
        if (note == nullptr || !note->alive)
        {
            continue;
        }
        bool hittable = false;
        double minHitTime = 180;
        double maxHitTime = 180;

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
        strumLineNotes[note->lane]->playAnimation("confirm");
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

    if (IsKeyPressed(KEY_F))
    {
        animatedNote->playAnimation("down confirm");
    }
    else if (IsKeyPressed(KEY_D))
    {
        animatedNote->playAnimation("left confirm");
    }
    else if (IsKeyPressed(KEY_J))
    {
        animatedNote->playAnimation("up confirm");
    }
    else if (IsKeyPressed(KEY_K))
    {
        animatedNote->playAnimation("right confirm");
    }
}

void funkin::PlayState::generateStaticArrows(bool player)
{
    for (int i = 0; i < 4; i++)
    {
        StrumNote *babyArrow = new StrumNote(42, 50, i, player);
        babyArrow->setPosition();
        strumLineNotes.push_back(babyArrow);
        add(babyArrow);
    }
}