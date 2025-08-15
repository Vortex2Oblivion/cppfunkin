#pragma once

#include "state.hpp"
#include "conductor.hpp"
#include "note.hpp"
#include "sparrowsprite.hpp"
#include "character.hpp"

namespace funkin
{
    class PlayState : public State
    {
    private:
        Conductor *_conductor;
        std::vector<bool> justHitArray = {false, false, false, false};

    public:
        PlayState(std::string song, std::string difficulty);
        ~PlayState();
        void generateStaticArrows(bool player);
        void loadSong(std::string song, std::string difficulty);
        void update(double delta);
        std::vector<raylib::Music *> tracks = {};
        std::vector<Note *> notes = {};
        std::vector<StrumNote *> strumLineNotes = {};
        Character *dad;
        raylib::Camera2D *camHUD;
    };
}