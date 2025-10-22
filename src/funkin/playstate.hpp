#pragma once

#include <nlohmann/json.hpp>

#include "../engine/bar.hpp"
#include "../engine/camera.hpp"
#include "../engine/sparrowsprite.hpp"
#include "../engine/text.hpp"
#include "character.hpp"
#include "conductor.hpp"
#include "musicbeatstate.hpp"
#include "note.hpp"
#include "playfield.hpp"
#include "song.hpp"

namespace funkin {

class PlayState : public MusicBeatState {
   private:
    void updateScoreText();

   public:
    PlayState(std::string songName, std::string difficulty);
    ~PlayState();
    void create();
    void loadSong(std::string songName, std::string difficulty);
    void update(float delta);
    void beatHit();
    void stepHit();

    std::vector<raylib::Music*> tracks = {};
    std::vector<funkin::PlayField*> playfields = {};

    funkin::PlayField* playerField;
    funkin::PlayField* dadField;

    funkin::Character* boyfriend;
    funkin::Character* dad;

    engine::Bar* healthBar;

    engine::Camera* camHUD;

    std::string songName;
    std::string difficulty;
    std::string curStage = "stage";
    std::string player1 = "bf";
    std::string player2 = "dad";
    float scrollSpeed = 1.0f;
    float defaultCameraZoom = 1.0f;
    funkin::SongData song;
    engine::Text* scoreText;
    int score = 0;
    float accuracy = 100.0f;
    raylib::Vector2 cameraTarget = raylib::Vector2();
    size_t totalPlayerNotes = 0;
    unsigned int misses = 0;
    float health = 50.0f;
};
}  // namespace funkin