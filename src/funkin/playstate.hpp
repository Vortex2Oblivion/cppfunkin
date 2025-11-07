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

        std::vector<raylib::Music *> tracks = {};
        std::vector<funkin::PlayField *> playfields = {};

        funkin::PlayField *playerField{};
        funkin::PlayField *dadField{};

        funkin::Stage *stage = nullptr;

        funkin::Character *boyfriend= nullptr;
        funkin::Character *dad = nullptr;
        funkin::Character *girlfriend = nullptr;

        funkin::HealthBar *healthBar = nullptr;

        engine::Camera *camHUD = nullptr;

        std::string songName;
        std::string difficulty;
        std::string curStage = "stage";
        std::string player1 = "bf";
        std::string player2 = "dad";
        float scrollSpeed = 1.0f;
        float defaultCameraZoom = 1.0f;
        funkin::SongData song;
        engine::Text *scoreText = nullptr;
        int score = 0;
        float accuracy = 100.0f;
        raylib::Vector2 cameraTarget = raylib::Vector2();
        size_t totalPlayerNotes = 0;
        uint16_t misses = 0;
        float health = 50.0f;
    };
} // namespace funkin