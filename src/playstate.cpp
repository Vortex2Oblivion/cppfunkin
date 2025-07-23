#include "playstate.hpp"
#include "note.hpp"
#include "strumnote.hpp"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std::filesystem;
using json = nlohmann::json;

playstate::playstate()
{
    loadSong("parasitic", "hard");
}

playstate::~playstate()
{
}

void playstate::loadSong(string song, string difficulty)
{
    string basePath = "assets/songs/" + song + "/";
    ifstream chartFile(basePath + difficulty + ".json");
    json parsedChart = json::parse(chartFile);
    tracks.push_back(new raylib::Music(basePath + "Inst.ogg"));
    tracks.push_back(new raylib::Music(basePath + "Voices.ogg"));

    vector<Color> colors = {PURPLE, BLUE, GREEN, RED};
    generateStaticArrows(false);
    generateStaticArrows(true);
    for (auto _note : parsedChart["song"]["notes"])
    {
        for (auto sectionNote : _note["sectionNotes"])
        {
            bool playerNote = (sectionNote[1] < 4) ? (!_note["mustHitSection"]) : (bool)(_note["mustHitSection"]);
            int lane = ((int)sectionNote[1] % 4) + (playerNote ? 4 : 0);
            note *__note = new note(sectionNote[0], lane % 4, parsedChart["song"]["speed"], strumLineNotes[lane]);
            __note->loadGraphic("assets/images/slungus.png");
            __note->color = colors[(int)sectionNote[1] % 4];
            __note->isPlayer = playerNote;
            notes.push_back(__note);
            add(__note);
        }
    }
    _conductor = new conductor(tracks);
    tracks[0]->Play();
    tracks[1]->Play();
}

void playstate::update(double delta)
{
    state::update(delta);
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

    double minHitTime = 180;
    double maxHitTime = 180;

    vector<note *> notesToDelete = {};
    justHitArray = {IsKeyPressed(KEY_D), IsKeyPressed(KEY_F), IsKeyPressed(KEY_J), IsKeyPressed(KEY_K)};
    for (auto note : notes)
    {
        if (note == nullptr || !note->alive)
        {
            continue;
        }
        bool hittable = false;
        if (note->strumTime < (_conductor->time * 1000 + minHitTime) && note->strumTime > (_conductor->time * 1000 - maxHitTime))
        {
            hittable = true;
        }
        if (!hittable || !justHitArray[note->lane])
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
}

void playstate::generateStaticArrows(bool player)
{
    for (int i = 0; i < 4; i++)
    {
        strumnote *babyArrow = new strumnote(42, 50, i, player);
        babyArrow->setPosition();
        babyArrow->loadGraphic("assets/images/slungus.png");
        strumLineNotes.push_back(babyArrow);
        add(babyArrow);
    }
}