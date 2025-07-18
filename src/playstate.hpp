#pragma once

#include "state.hpp"
#include "conductor.hpp"
#include "note.hpp"

class playstate : public state
{
private:
    conductor* _conductor;
public:
    playstate();
    ~playstate();
    void loadSong(string song, string difficulty);
    void update(double delta);
    vector<raylib::Music *> tracks = {};
    vector<note *> notes = {};
};