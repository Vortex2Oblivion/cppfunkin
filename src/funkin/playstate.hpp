#pragma once

#include <nlohmann/json.hpp>

#include "../engine/camera.hpp"
#include "../engine/sparrowsprite.hpp"
#include "../engine/text.hpp"
#include "character.hpp"
#include "conductor.hpp"
#include "healthbar.hpp"
#include "musicbeatstate.hpp"
#include "playfield.hpp"
#include "song.hpp"
#include "stage.hpp"

namespace funkin
{

    class PlayState final : public MusicBeatState
    {
    private:
        void updateScoreText() const;

    public:
        PlayState(std::string songName, std::string difficulty);
        ~PlayState() override;

        void create() override;
        void update(float delta) override;
        void beatHit() override;
        void stepHit() override;

        void loadSong(const std::string &songName,
                      const std::string &difficulty);
        void focusCamera(void);

        std::vector<std::shared_ptr<raylib::Music>> tracks = {};
        std::vector<std::shared_ptr<funkin::PlayField>> playfields = {};

        std::shared_ptr<funkin::PlayField> playerField = nullptr;
        std::shared_ptr<funkin::PlayField> dadField = nullptr;

        std::shared_ptr<funkin::Stage> stage = nullptr;

        std::shared_ptr<funkin::Character> boyfriend= nullptr;
        std::shared_ptr<funkin::Character>dad = nullptr;
        std::shared_ptr<funkin::Character> girlfriend = nullptr;

        std::shared_ptr<funkin::HealthBar> healthBar = nullptr;

        std::shared_ptr<engine::Camera> camHUD = nullptr;

        std::string songName;
        std::string difficulty;
        std::string curStage = "stage";
        std::string player1 = "bf";
        std::string player2 = "dad";
        std::string spectator = "gf";

        float scrollSpeed = 1.0f;
        float defaultCameraZoom = 1.0f;
        funkin::SongData song;
        std::shared_ptr<engine::Text> scoreText = nullptr;
        int score = 0;
        float accuracy = 100.0f;
        raylib::Vector2 cameraTarget = raylib::Vector2();
        size_t totalPlayerNotes = 0;
        uint16_t misses = 0;
        float health = 50.0f;
    };
} // namespace funkin