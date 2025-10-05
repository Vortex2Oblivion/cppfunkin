#pragma once

#include "character.hpp"
#include "conductor.hpp"
#include "musicbeatstate.hpp"
#include "note.hpp"
#include "song.hpp"
#include "../engine/camera.hpp"
#include "../engine/sparrowsprite.hpp"
#include "../engine/text.hpp"
#include <nlohmann/json.hpp>

namespace funkin
{


    class PlayState : public MusicBeatState
    {
    private:
        void updateScoreText();
        void calculateAccuracy();

    public:
        PlayState(std::string song, std::string difficulty);
        ~PlayState();
        void loadSong(std::string song, std::string difficulty);
        void update(float delta);
        void beatHit();
        void stepHit();
        std::vector<raylib::Music *> tracks = {};
        std::vector<Note *> notes = {};
        std::vector<StrumNote *> strumLineNotes = {};
        Character *boyfriend;
        Character *dad;
        engine::Camera *camHUD;
        std::string curStage = "stage";
        std::string player1 = "bf";
        std::string player2 = "dad";
        float scrollSpeed = 1.0f;
        float defaultCameraZoom = 1.0f;
        funkin::SongData song;
        engine::Text *scoreText;
        int score = 0;
        float accuracy = 100.0f;
        raylib::Vector2 cameraTarget = raylib::Vector2();
        int playerNotes = 0;
        unsigned int misses = 0;
    };
}