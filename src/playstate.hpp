#pragma once

#include "musicbeatstate.hpp"
#include "conductor.hpp"
#include "note.hpp"
#include "sparrowsprite.hpp"
#include "character.hpp"
#include "camera.hpp"
#include <nlohmann/json.hpp>
#include "text.hpp"

namespace funkin
{
    struct NoteData
    {
        float time;
        int lane;
        bool isPlayer;
    };

    class PlayState : public MusicBeatState
    {
    private:
        const std::vector<std::string> singAnimArray = {"singLEFT", "singDOWN", "singUP", "singRIGHT"};
        std::vector<bool> justHitArray = {false, false, false, false};
        std::vector<bool> pressedArray = {false, false, false, false};
        std::vector<NoteData> noteDatas;
        size_t noteDataIndex = 0;

        void invalidateNote(Note *note);
        void updateScoreText();
        void calculateAccuracy();

    public:
        PlayState(std::string song, std::string difficulty);
        ~PlayState();
        void generateStaticArrows(bool player);
        void loadSong(std::string song, std::string difficulty);
        void update(float delta);
        void beatHit();
        void stepHit();
        std::vector<raylib::Music *> tracks = {};
        std::vector<Note *> notes = {};
        std::vector<StrumNote *> strumLineNotes = {};
        Character *boyfriend;
        Character *dad;
        funkin::Camera *camHUD;
        std::string curStage = "stage";
        std::string player1 = "bf";
        std::string player2 = "dad";
        float scrollSpeed = 1.0f;
        float defaultCameraZoom = 1.0f;
        nlohmann::json_abi_v3_12_0::json song;
        funkin::Text *scoreText;
        int score = 0;
        float accuracy = 100.0f;
        raylib::Vector2 cameraTarget = raylib::Vector2();
        int totalNotes = 0;
        unsigned int misses = 0;
    };
}