#pragma once

#include "state.hpp"
#include "conductor.hpp"
#include "note.hpp"
#include "sparrowsprite.hpp"
#include "character.hpp"

namespace funkin
{
    struct NoteData
    {
        double time;
        int lane;
        bool isPlayer;
    };

    class PlayState : public State
    {
    private:
        Conductor *_conductor;
        std::vector<bool> justHitArray = {false, false, false, false};
        std::vector<NoteData> noteDatas;
        size_t noteDataIndex = 0;
        double scrollSpeed = 1.0;

    public:
        PlayState(std::string song, std::string difficulty);
        ~PlayState();
        void generateStaticArrows(bool player);
        void loadSong(std::string song, std::string difficulty);
        void update(double delta);
        std::vector<raylib::Music *> tracks = {};
        std::vector<Note *> notes = {};
        std::vector<StrumNote *> strumLineNotes = {};
        Character *boyfriend;
        Character *dad;
        raylib::Camera2D *camHUD;
    };
}