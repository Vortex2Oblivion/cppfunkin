#pragma once

#include "state.hpp"
#include "conductor.hpp"
#include "note.hpp"

class playstate : public state
{
private:
    conductor* _conductor;
    vector<bool> justHitArray = {false, false, false, false};
public:
    playstate();
    ~playstate();
    void generateStaticArrows(bool player);
    void loadSong(string song, string difficulty);
    void update(double delta);
    vector<raylib::Music *> tracks = {};
    vector<note *> notes = {};
    vector<strumnote *> strumLineNotes = {};
};