#include "songselectstate.hpp"

#include "../engine/game.hpp"
#include "Functions.hpp"
#include "playstate.hpp"

funkin::SongSelectState::SongSelectState() : MusicBeatState() {
    std::string songListRaw = raylib::LoadFileText("assets/songs/list.txt");
    std::vector<std::string> songList = raylib::TextSplit(songListRaw, '\n');
    for (std::string song : songList) {
        if (!song.empty()) {
            songs.push_back(song);
        }
    }
}

funkin::SongSelectState::~SongSelectState() { songs.clear(); }

void funkin::SongSelectState::create() {
    funkin::MusicBeatState::create();
    songText = new engine::Text(songs[selectedSong], 20, 100, 100);
    add(songText);

    slungus = new engine::Sprite(400, 200);
    slungus->loadGraphic("assets/images/slungus.png");
    add(slungus);
}

void funkin::SongSelectState::update(float delta) {
    if (IsKeyPressed(KEY_RIGHT)) {
        selectedSong++;
        if (selectedSong >= (int)songs.size()) {
            selectedSong = 0;
        }
    } else if (IsKeyPressed(KEY_LEFT)) {
        selectedSong--;
        if (selectedSong < 0) {
            selectedSong = (int)songs.size() - 1;
        }
    }
    songText->text = songs[selectedSong];
    slungus->scale.x = (float)sin(raylib::Window::GetTime()) + 2.0f;
    slungus->scale.y = (float)cos(raylib::Window::GetTime()) + 2.0f;
    if (IsKeyPressed(KEY_ENTER)) {
        engine::Game::switchState(new funkin::PlayState(songs[selectedSong], "hard"));
    }
}
