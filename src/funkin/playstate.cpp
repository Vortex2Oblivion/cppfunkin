#include "playstate.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <raymath.hpp>

#include "../engine/animatedsprite.hpp"
#include "../engine/camera.hpp"
#include "../engine/game.hpp"
#include "../engine/text.hpp"
#include "coolutil.hpp"
#include "healthbar.hpp"
#include "healthicon.hpp"
#include "note.hpp"
#include "playfield.hpp"
#include "song.hpp"
#include "songselectstate.hpp"
#include "strumnote.hpp"

funkin::PlayState::PlayState(std::string songName, std::string difficulty) : MusicBeatState() {
    this->songName = songName;
    this->difficulty = difficulty;
}

funkin::PlayState::~PlayState() { playfields.clear(); }

void funkin::PlayState::create() {
    funkin::MusicBeatState::create();
    camHUD = new engine::Camera();
    engine::Game::cameras.push_back(camHUD);

    loadSong(songName, difficulty);

    dad = new Character(0, 0, player2);
    boyfriend = new Character(0, 0, player1);

    std::string stagePath = "assets/stages/" + curStage + "/";
    std::ifstream stageFile(stagePath + "stage.json");
    if (!stageFile.fail()) {
        nlohmann::json parsedStage = nlohmann::json::parse(stageFile);
        stageFile.close();

        for (auto objects : parsedStage["objects"]) {
            engine::Sprite* object = new engine::Sprite(objects["position"][0], objects["position"][1]);
            if (objects.contains("extension")) {
                object->loadGraphic(stagePath + (std::string)objects["file"] + (std::string)objects["extension"]);
            } else {
                object->loadGraphic(stagePath + (std::string)objects["file"] + ".png");
            }
            if (objects.count("scale")) {
                object->scale.x = objects["scale"][0];
                object->scale.y = objects["scale"][1];
                object->origin *= object->scale;
            }
            object->centerOrigin();
            add(object);
        }

        defaultCameraZoom = engine::Game::defaultCamera->zoom = parsedStage["zoom"];

        auto dadPosition = parsedStage["characters"]["dad"];
        auto boyfriendPosition = parsedStage["characters"]["bf"];
        dad->position += raylib::Vector2(dadPosition["x"], dadPosition["y"]);
        boyfriend->position += raylib::Vector2(boyfriendPosition["x"], boyfriendPosition["y"]);
    } else {
        boyfriend->position.x = 400;
    }

    add(dad);
    add(boyfriend);

    dadField = new PlayField(0, 0, this->song.opponentNotes, {dad}, true);
    dadField->camera = camHUD;
    dadField->conductor = conductor;
    dadField->scrollSpeed = scrollSpeed;
    add(dadField);

    playfields.push_back(dadField);

    playerField = new PlayField(raylib::Window::GetWidth() / 2.0f, 0, this->song.playerNotes, {boyfriend}, false);
    playerField->camera = camHUD;
    playerField->conductor = conductor;
    playerField->scrollSpeed = scrollSpeed;
    add(playerField);

    playfields.push_back(playerField);

    // https://www.raylib.com/examples/text/loader.html?name=text_codepoints_loading
    std::string defaultScoreText = "Score: 0123456789 • Misses: 0 • Accuracy: 100.0%";

    // Convert each utf-8 character into its
    // corresponding codepoint in the font file
    int codepointCount = 0;
    int* codepoints = LoadCodepoints(defaultScoreText.c_str(), &codepointCount);

    // Removed duplicate codepoints to generate smaller font atlas
    int codepointsNoDupsCount = 0;
    int* codepointsNoDups = funkin::CoolUtil::codepointRemoveDuplicates(codepoints, codepointCount, &codepointsNoDupsCount);
    UnloadCodepoints(codepoints);

    scoreText = new engine::Text("", 24, 100, 100);
    scoreText->position.y = raylib::Window::GetHeight() * 0.9f;
    scoreText->font = raylib::Font("assets/fonts/vcr.ttf", 24, codepointsNoDups, codepointsNoDupsCount);
    scoreText->outlineSize = 2.0f;
    scoreText->camera = camHUD;
    
    delete codepointsNoDups;
    
    updateScoreText();
    
    healthBar = new funkin::HealthBar(0.0f, scoreText->position.y - 30.0f, dad->characterName, boyfriend->characterName, raylib::RED, raylib::GREEN);
    healthBar->camera = camHUD;
    healthBar->bar->screenCenter(engine::Axes::X);
    add(healthBar);
    
    add(scoreText);
}

void funkin::PlayState::loadSong(std::string songName, std::string difficulty) {
    bool needsVoices;
    std::string basePath = "assets/songs/" + songName + "/";

    song = funkin::Song::parseChart(songName, difficulty);

    nlohmann::json_abi_v3_12_0::json parsedSong = song.parsedSong;

    scrollSpeed = parsedSong["speed"];
    needsVoices = parsedSong["needsVoices"];
    curStage = parsedSong["stage"];
    player1 = parsedSong["player1"];
    player2 = parsedSong["player2"];

    // noteDatas = song.notes;
    totalPlayerNotes = song.playerNotes.size();

    if (FileExists((basePath + "Inst.ogg").c_str())) {
        tracks.push_back(new raylib::Music(basePath + "Inst.ogg"));
    }
    if (needsVoices) {
        if (raylib::FileExists(basePath + "Voices_Player.ogg") && raylib::FileExists(basePath + "Voices_Opponent.ogg")) {
            tracks.push_back(new raylib::Music(basePath + "Voices_Player.ogg"));
            tracks.push_back(new raylib::Music(basePath + "Voices_Opponent.ogg"));
        } else if (raylib::FileExists(basePath + "Voices.ogg")) {
            tracks.push_back(new raylib::Music(basePath + "Voices.ogg"));
        }
    }

    for (raylib::Music* music : tracks) {
        music->SetLooping(false);
    }

    conductor->start(tracks);
    // TODO: BPM Changes
    conductor->bpm = parsedSong["bpm"];
}

void funkin::PlayState::beatHit() {
    funkin::MusicBeatState::beatHit();
    for (auto field : playfields) {
        for (auto character : field->characters) {
            character->dance();
        }
    }
    if (conductor->getBeat() % 4 == 0) {
        if (engine::Game::defaultCamera->zoom < 1.35f) {
            engine::Game::defaultCamera->zoom += 0.015f;
            camHUD->zoom += 0.03f;
        }
        int targetSection = (int)fminf((float)song.parsedSong["notes"].size() - 1.0f, fmaxf(0, floor(conductor->getBeat() / 4.0f)));
        if (song.parsedSong["notes"][targetSection]["mustHitSection"]) {
            cameraTarget = boyfriend->getMidpoint() - raylib::Vector2(640, 360) - raylib::Vector2(100, 100);
        } else {
            cameraTarget = dad->getMidpoint() - raylib::Vector2(640, 360) + raylib::Vector2(150, -100);
        }
    }
    healthBar->bopIcons(1.2f);
}

void funkin::PlayState::stepHit() { funkin::MusicBeatState::stepHit(); }

void funkin::PlayState::updateScoreText() {
    scoreText->text = TextFormat("Score: %i • Misses: %i • Accuracy: %.2f%%", playerField->score, playerField->misses, playerField->accuracy);
    scoreText->screenCenter(engine::Axes::X);
}

void funkin::PlayState::update(float delta) {
    MusicBeatState::update(delta);

    engine::Game::defaultCamera->zoom = Lerp(defaultCameraZoom, engine::Game::defaultCamera->zoom, expf(-delta * 3.125f));
    camHUD->zoom = Lerp(1, camHUD->zoom, expf(-delta * 3.125f));
    engine::Game::defaultCamera->cameraPosition =
        engine::Game::defaultCamera->cameraPosition.Lerp(cameraTarget, 1.0f - powf(1.0f - 0.04f, delta * 60.0f));

    updateScoreText();

    healthBar->bar->percent = health = playerField->health;

    bool playing = false;
    for (raylib::Music* music : tracks) {
        if (music->IsPlaying()) {
            playing = true;
            break;
        }
    }

    if (!playing || IsKeyPressed(KEY_SPACE)) {
        engine::Game::switchState(new SongSelectState());
    }
}
