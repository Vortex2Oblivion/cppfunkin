#include "playstate.hpp"
#include "note.hpp"
#include "strumnote.hpp"
#include "sparrowsprite.hpp"
#include "game.hpp"
#include "camera.hpp"
#include "text.hpp"
#include "song.hpp"
#include <filesystem>
#include <fstream>
#include <raymath.hpp>
#include <exception>
#include <algorithm>
#include <nlohmann/json.hpp>

funkin::PlayState::PlayState(std::string song, std::string difficulty)
{
    camHUD = new funkin::Camera();
    funkin::Game::cameras.push_back(camHUD);

    loadSong(song, difficulty);

    dad = new Character(0, 0, player2);
    boyfriend = new Character(0, 0, player1);

    std::string stagePath = "assets/stages/" + curStage + "/";
    std::ifstream stageFile(stagePath + "stage.json");
    if (!stageFile.fail())
    {
        nlohmann::json parsedStage = nlohmann::json::parse(stageFile);
        stageFile.close();

        for (auto objects : parsedStage["objects"])
        {
            Sprite *object = new Sprite(objects["position"][0], objects["position"][1]);
            object->loadGraphic(stagePath + (std::string)objects["file"] + ".png");
            if (objects.count("scale"))
            {
                object->scale.x = objects["scale"][0];
                object->scale.y = objects["scale"][1];
            }
            add(object);
        }

        defaultCameraZoom = funkin::Game::defaultCamera->zoom = parsedStage["zoom"];
        dad->position += raylib::Vector2(parsedStage["characters"]["dad"]["x"], parsedStage["characters"]["dad"]["y"]);
        boyfriend->position += raylib::Vector2(parsedStage["characters"]["bf"]["x"], parsedStage["characters"]["bf"]["y"]);
    }
    else
    {
        boyfriend->position.x = 400;
    }

    add(dad);
    add(boyfriend);

    scoreText = new funkin::Text("Score: 0 | Misses: 0 | Accuracy: 0", 24, 100, 100);
    scoreText->position.y = GetScreenHeight() * 0.9f;
    scoreText->setFont("assets/fonts/vcr.ttf");
    scoreText->camera = camHUD;
    scoreText->screenCenter();
    add(scoreText);
}

funkin::PlayState::~PlayState()
{
}

bool noteDataSorter(funkin::NoteData a, funkin::NoteData b)
{
    return a.time < b.time;
}

void funkin::PlayState::loadSong(std::string songName, std::string difficulty)
{
    bool needsVoices;
    std::string basePath = "assets/songs/" + songName + "/";

    song = funkin::Song::parseChart(songName, difficulty);

    generateStaticArrows(true);
    generateStaticArrows(false);

    // TODO: Move more of this into its own class
    // TODO: Load Psych V1 charts properly.

    scrollSpeed = song["speed"];
    needsVoices = song["needsVoices"];
    curStage = song["stage"];
    player1 = song["player1"];
    player2 = song["player2"];

    for (auto sectionNotes : song["notes"])
    {
        for (auto sectionNote : sectionNotes["sectionNotes"])
        {
            bool playerNote = (sectionNote[1] < 4) ? (bool)(sectionNotes["mustHitSection"]) : (!sectionNotes["mustHitSection"]);
            int lane = ((int)sectionNote[1] % 4) + (playerNote ? 0 : 4);
            noteDatas.push_back(NoteData{
                (float)sectionNote[0] / 1000.0f, // time
                lane % 4,                        // lane
                playerNote,                      // isPlayer
            });
        }
    }

    tracks.push_back(new raylib::Music(basePath + "Inst.ogg"));
    if (needsVoices)
    {
        tracks.push_back(new raylib::Music(basePath + "Voices.ogg"));
    }

    std::sort(noteDatas.begin(), noteDatas.end(), noteDataSorter);

    conductor->start(tracks);
    // TODO: BPM Changes
    conductor->bpm = song["bpm"];
}

void funkin::PlayState::beatHit()
{
    funkin::MusicBeatState::beatHit();
    dad->dance();
    boyfriend->dance();
    if (conductor->getBeat() % 4 == 0)
    {
        if (funkin::Game::defaultCamera->zoom < 1.35f)
        {
            funkin::Game::defaultCamera->zoom += 0.015f;
            camHUD->zoom += 0.03f;
        }
        if (song["notes"][(int)fmaxf(0, floor(conductor->getBeat() / 4.0f))]["mustHitSection"])
        {
            cameraTarget = boyfriend->getMidpoint() - raylib::Vector2(640, 360) - raylib::Vector2(100, 100);
        }
        else
        {
            cameraTarget = dad->getMidpoint() - raylib::Vector2(640, 360) + raylib::Vector2(150, -100);
        }
    }
}

void funkin::PlayState::stepHit()
{
    funkin::MusicBeatState::stepHit();
}

void funkin::PlayState::update(float delta)
{
    MusicBeatState::update(delta);
    while (noteDataIndex < noteDatas.size() && conductor->time >= noteDatas[noteDataIndex].time - 1.0)
    {
        NoteData data = noteDatas[noteDataIndex];
        Note *note = new Note(data.time * 1000.0f, data.lane, scrollSpeed, strumLineNotes[data.lane + (!data.isPlayer ? 4 : 0)]);
        note->camera = camHUD;
        note->isPlayer = data.isPlayer;
        notes.push_back(note);
        add(note);
        noteDataIndex++;
    }

    std::vector<Note *> notesToDelete;
    for (auto note : notes)
    {
        if (!note->alive)
        {
            continue;
        }

        if (conductor->time * 1000.0 > note->strumTime + 180.0)
        {
            notesToDelete.push_back(note);
            note->alive = false;
        }
        else
        {
            note->songPos = conductor->time;
        }
    }

    // inputs
    // thanks for helping my dumbass with this rudy
    float closestDistance = INFINITY;

    pressedArray = {IsKeyDown(KEY_D), IsKeyDown(KEY_F), IsKeyDown(KEY_J), IsKeyDown(KEY_K)};
    justHitArray = {IsKeyPressed(KEY_D), IsKeyPressed(KEY_F), IsKeyPressed(KEY_J), IsKeyPressed(KEY_K)};

    for (size_t lane = 0; lane < justHitArray.size(); lane++)
    {
        if (justHitArray[lane])
        {
            strumLineNotes[lane]->playAnimation("press");
            strumLineNotes[lane]->offset = strumLineNotes[lane]->offset.Scale(0.0f);
        }
    }

    for (auto note : notes)
    {
        if (note == nullptr || !note->alive)
        {
            continue;
        }
        bool hittable = false;
        float minHitTime = 180.0f;
        float maxHitTime = 180.0f;

        if (!note->isPlayer)
        {
            minHitTime = 0;
        }
        if (note->strumTime < (conductor->time * 1000 + minHitTime) && note->strumTime > (conductor->time * 1000 - maxHitTime))
        {
            hittable = true;
        }
        if (!hittable || (!justHitArray[note->lane] && note->isPlayer))
        {
            continue;
        }
        float rawHitTime = note->strumTime - conductor->time * 1000.f;
        float distance = abs(rawHitTime);
        if (distance < closestDistance)
        {
            closestDistance = distance;
        }
        else
        {
            continue;
        }
        int lane = note->lane;
        if (!note->isPlayer)
        {
            dad->playAnimation(singAnimArray[lane]);
            lane += 4;
        }
        else
        {
            totalNotes++;
            boyfriend->playAnimation(singAnimArray[lane]);
            int addScore = abs(500 - (note->strumTime - conductor->time) / 1000.0f);
            score += addScore;
            accuracy = (100.0f / (totalNotes / hitNotes));
            scoreText->setText(TextFormat("Score: %i | Misses: %i | Accuracy: %f", score, 0, accuracy));
            scoreText->screenCenter();
        }
        strumLineNotes[lane]->playAnimation("confirm");
        strumLineNotes[lane]->centerOffsets();
        strumLineNotes[lane]->offset = strumLineNotes[lane]->offset.Scale(0.5f);
        // strumLineNotes[lane]->offset.x = -30;
        // strumLineNotes[lane]->offset.y = -30;
        notesToDelete.push_back(note);
    }

    for (auto note : notesToDelete)
    {
        notes.erase(find(notes.begin(), notes.end(), note));
        remove(note);
    }
    for (auto track : tracks)
    {
        track->Update();
    }

    for (auto strum : strumLineNotes)
    {
        if (strum->player)
        {
            if (!pressedArray[strum->lane])
            {
                strum->playAnimation("static");
                strum->offset.x = strum->offset.y = 0.0;
            }
        }
        else
        {
            if (strum->currentAnimation->currentFrame >= strum->currentAnimation->frames.size() - 1)
            {
                strum->playAnimation("static");
                strum->offset.x = strum->offset.y = 0.0;
            }
        }
    }

    funkin::Game::defaultCamera->zoom = Lerp(defaultCameraZoom, funkin::Game::defaultCamera->zoom, expf(-delta * 3.125f));
    camHUD->zoom = Lerp(1, camHUD->zoom, expf(-delta * 3.125f));
    funkin::Game::defaultCamera->cameraPosition = Vector2Lerp(funkin::Game::defaultCamera->cameraPosition, cameraTarget, 1.0f - powf(1.0 - 0.04, delta * 60.0f));
}

void funkin::PlayState::generateStaticArrows(bool player)
{
    for (int i = 0; i < 4; i++)
    {
        StrumNote *babyArrow = new StrumNote(42, 50, i, player);
        babyArrow->setPosition();
        babyArrow->camera = camHUD;
        strumLineNotes.push_back(babyArrow);
        add(babyArrow);
    }
}
