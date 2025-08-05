#pragma once

#include "state.hpp"
#include "conductor.hpp"
#include "note.hpp"

namespace funkin
{
    class PlayState : public State
    {
    private:
        Conductor *_conductor;
        vector<bool> justHitArray = {false, false, false, false};

    public:
        PlayState();
        ~PlayState();
        void generateStaticArrows(bool player);
        void loadSong(string song, string difficulty);
        void update(double delta);
        vector<raylib::Music *> tracks = {};
        vector<Note *> notes = {};
        vector<StrumNote *> strumLineNotes = {};
    };
}