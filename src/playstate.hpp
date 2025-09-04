#pragma once

#include "musicbeatstate.hpp"
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

    class PlayState : public MusicBeatState
    {
    private:
        std::vector<bool> justHitArray = {false, false, false, false};
        std::vector<bool> pressedArray = {false, false, false, false};
        std::vector<NoteData> noteDatas;
        size_t noteDataIndex = 0;
        double scrollSpeed = 1.0;

    public:
        PlayState(std::string song, std::string difficulty);
        ~PlayState();
        void generateStaticArrows(bool player);
        void loadSong(std::string song, std::string difficulty);
        void update(double delta);
        void beatHit();
        std::vector<raylib::Music *> tracks = {};
        std::vector<Note *> notes = {};
        std::vector<StrumNote *> strumLineNotes = {};
        Character *boyfriend;
        Character *dad;
        raylib::Camera2D *camHUD;
        std::string curStage = "stage";
        std::string player1 = "bf";
        std::string player2 = "dad";
    };
}