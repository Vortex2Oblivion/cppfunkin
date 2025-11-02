#include "songselectstate.hpp"

#include "../engine/game.hpp"
#include "Functions.hpp"
#include "playstate.hpp"

funkin::SongSelectState::SongSelectState() : MusicBeatState() {
    const std::string songListRaw = raylib::LoadFileText("assets/songs/list.txt");
    const std::vector<std::string> songList = raylib::TextSplit(songListRaw, '\n');
    for (const auto& song : songList) {
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
        if (selectedSong >= static_cast<int>(songs.size())) {
            selectedSong = 0;
        }
    } else if (IsKeyPressed(KEY_LEFT)) {
        selectedSong--;
        if (selectedSong < 0) {
            selectedSong = static_cast<int>(songs.size()) - 1;
        }
    }
    songText->text = songs[selectedSong];
    slungus->scale.x = static_cast<float>(sin(raylib::Window::GetTime())) + 2.0f;
    slungus->scale.y = static_cast<float>(cos(raylib::Window::GetTime())) + 2.0f;
    if (raylib::Keyboard::IsKeyPressed(KEY_ENTER)) {
        engine::Game::switchState(new funkin::PlayState(songs[selectedSong], "hard"));
    }
}
