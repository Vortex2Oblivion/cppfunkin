#include "playstate.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <raymath.hpp>
#include <utility>

#include "../engine/animatedsprite.hpp"
#include "../engine/camera.hpp"
#include "../engine/game.hpp"
#include "../engine/text.hpp"
#include "coolutil.hpp"
#include "healthbar.hpp"
#include "playfield.hpp"
#include "raylib.h"
#include "song.hpp"
#include "songselectstate.hpp"

funkin::PlayState::PlayState(std::string songName, std::string difficulty) : MusicBeatState() {
    this->songName = std::move(songName);
    this->difficulty = std::move(difficulty);
}

funkin::PlayState::~PlayState() {
    playfields.clear();
    ShowCursor();
}

void funkin::PlayState::create() {
    HideCursor();

    funkin::MusicBeatState::create();

    camHUD = std::make_shared<engine::Camera>();
    engine::Game::cameras.push_back(camHUD);

    loadSong(songName, difficulty);

    dad = std::make_shared<Character>(0, 0, player2, false);

    boyfriend = std::make_shared<Character>(0, 0, player1, true);

    girlfriend = std::make_shared<Character>(0, 0, "gf", false);
    girlfriend->scrollFactor = raylib::Vector2(0.95f, 0.95f);

    stage = std::make_shared<funkin::Stage>(curStage, boyfriend, dad, girlfriend);
    add(stage);


    engine::Game::defaultCamera->zoom = defaultCameraZoom = stage->zoom;

    dadField = std::shared_ptr<funkin::PlayField>(new funkin::PlayField(0, 0, this->song.opponentNotes, {dad}, true));
    dadField->camera = camHUD;
    dadField->conductor = conductor;
    dadField->scrollSpeed = scrollSpeed;
    add(dadField);

    playfields.push_back(dadField);

    playerField = std::shared_ptr<funkin::PlayField>(new PlayField(static_cast<float>(raylib::Window::GetWidth()) / 2.0f, 0, this->song.playerNotes, {boyfriend}, false));
    playerField->camera = camHUD;
    playerField->conductor = conductor;
    playerField->scrollSpeed = scrollSpeed;
    add(playerField);

    playfields.push_back(playerField);

    // https://www.raylib.com/examples/text/loader.html?name=text_codepoints_loading
    const auto defaultScoreText = "Score: 0123456789 • Misses: 0 • Accuracy: 100.0%";

    // Convert each utf-8 character into its
    // corresponding codepoint in the font file
    int codepointCount = 0;
    int* codepoints = LoadCodepoints(defaultScoreText, &codepointCount);

    // Removed duplicate codepoints to generate smaller font atlas
    int codepointsNoDupsCount = 0;
    int* codepointsNoDups = funkin::CoolUtil::codepointRemoveDuplicates(codepoints, codepointCount, &codepointsNoDupsCount);
    UnloadCodepoints(codepoints);

    scoreText = std::make_shared<engine::Text>("", 24, 100, 100);
    scoreText->position.y = static_cast<float>(raylib::Window::GetHeight()) * 0.9f;
    scoreText->font = raylib::Font("assets/fonts/vcr.ttf", 24, codepointsNoDups, codepointsNoDupsCount);
    scoreText->outlineSize = 2.0f;
    scoreText->camera = camHUD;

    delete codepointsNoDups;

    updateScoreText();

    healthBar = std::make_shared<funkin::HealthBar>(0.0f, scoreText->position.y - 30.0f, dad->characterName, boyfriend->characterName, raylib::RED, raylib::GREEN);
    healthBar->camera = camHUD;
    healthBar->bar->screenCenter(engine::Axes::X);
    add(healthBar);

    add(scoreText);

    focusCamera();
    engine::Game::defaultCamera->cameraPosition = cameraTarget;
}

void funkin::PlayState::loadSong( const std::string& songName,  const std::string& difficulty) {
    const std::string basePath = "assets/songs/" + songName + "/";

    song = funkin::Song::parseChart(songName, difficulty);

    nlohmann::json_abi_v3_12_0::json parsedSong = song.parsedSong;

    const bool needsVoices = parsedSong["needsVoices"];
    scrollSpeed = parsedSong["speed"];
    curStage = parsedSong["stage"];
    player1 = parsedSong["player1"];
    player2 = parsedSong["player2"];

    // noteDatas = song.notes;
    totalPlayerNotes = song.playerNotes.size();

    if (raylib::FileExists(basePath + "Inst.ogg")) {
        tracks.push_back(std::make_shared<raylib::Music>(basePath + "Inst.ogg"));
    }
    if (needsVoices) {
        if (raylib::FileExists(basePath + "Voices_Player.ogg") && raylib::FileExists(basePath + "Voices_Opponent.ogg")) {
            tracks.push_back(std::make_shared<raylib::Music>(basePath + "Voices_Player.ogg"));
            tracks.push_back(std::make_shared<raylib::Music>(basePath + "Voices_Opponent.ogg"));
        } else if (raylib::FileExists(basePath + "Voices.ogg")) {
            tracks.push_back(std::make_shared<raylib::Music>(basePath + "Voices.ogg"));
        }
    }

    for (const auto music : tracks) {
        music->looping = false;
    }

    conductor->start(tracks);
    // TODO: BPM Changes
    conductor->bpm = parsedSong["bpm"];
}

void funkin::PlayState::focusCamera(void) {
    if (song.parsedSong.contains("notes")) {
        auto notes = song.parsedSong["notes"];
        const int targetSection = static_cast<int>(fminf(static_cast<float>(notes.size()) - 1.0f, fmaxf(0, floor(static_cast<float>(conductor->getBeat()) / 4.0f))));

        if (notes[targetSection]["mustHitSection"]) {
            cameraTarget = boyfriend->getMidpoint() + boyfriend->cameraOffset - raylib::Vector2(100, 100);
        } else {
            cameraTarget = dad->getMidpoint() + dad->cameraOffset + raylib::Vector2(150, -100);
        }
    }
}

void funkin::PlayState::beatHit() {
    funkin::MusicBeatState::beatHit();

    dad->dance();
    boyfriend->dance();
    girlfriend->dance();

    if (conductor->getBeat() % 4 == 0) {
        if (engine::Game::defaultCamera->zoom < 1.35f) {
            engine::Game::defaultCamera->zoom += 0.015f;
            camHUD->zoom += 0.03f;
        }

        focusCamera();
    }

    healthBar->bopIcons(1.125f);
}

void funkin::PlayState::stepHit() { funkin::MusicBeatState::stepHit(); }

void funkin::PlayState::updateScoreText() const {
    scoreText->text = TextFormat("Score: %i • Misses: %i • Accuracy: %.2f%%", playerField->score, playerField->misses, playerField->accuracy);
    scoreText->screenCenter(engine::Axes::X);
}

void funkin::PlayState::update(const float delta) {
    MusicBeatState::update(delta);

    engine::Game::defaultCamera->zoom = Lerp(defaultCameraZoom, engine::Game::defaultCamera->zoom, expf(-delta * 3.125f));
    camHUD->zoom = Lerp(1, camHUD->zoom, expf(-delta * 3.125f));
    engine::Game::defaultCamera->cameraPosition =
        engine::Game::defaultCamera->cameraPosition.Lerp(cameraTarget, 1.0f - powf(1.0f - 0.04f, delta * 60.0f));

    updateScoreText();

    healthBar->bar->percent = health = playerField->health;

    bool playing = false;
    for (const auto music : tracks) {
        if (music->IsPlaying()) {
            playing = true;
            break;
        }
    }

    if (!playing || IsKeyPressed(KEY_SPACE)) {
        engine::Game::switchState(std::make_unique<SongSelectState>());
    }
}
