#include "playstate.hpp"
#include "note.hpp"
#include <iostream>
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
    for (auto _note : parsedChart["song"]["notes"])
    {
        for (auto sectionNote : _note["sectionNotes"])
        {
            bool playerNote = (sectionNote[1] < 4) ? (!_note["mustHitSection"]) : (bool)(_note["mustHitSection"]);
            note * __note = new note(sectionNote[0], ((int)sectionNote[1] % 4) + (playerNote ? 0 : 4), parsedChart["song"]["speed"]);
            __note->loadGraphic("assets/images/slungus.png");
            __note->color = colors[(int)sectionNote[1] % 4];
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
        note->songPos = _conductor->time;
    }
    for(auto track : tracks){
        track->Update();
    }
}