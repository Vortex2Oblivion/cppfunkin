#include "songselectstate.hpp"

#include "alphabet.hpp"
#include "playstate.hpp"

#include <game.hpp>

funkin::SongSelectState::SongSelectState() : MusicBeatState() {}

funkin::SongSelectState::~SongSelectState() { songs.clear(); }

void funkin::SongSelectState::create() {
    funkin::MusicBeatState::create();

    const std::string songListRaw = raylib::LoadFileText("assets/songs/list.txt");
    const std::vector<std::string> songList = raylib::TextSplit(songListRaw, '\n');
    for (const auto& song : songList) {
        if (!song.empty()) {
            songs.push_back(song);
        }
    }

    songText = std::make_shared<engine::Text>(songs[selectedSong], 20, 100, 100);
    add(songText);

    slungus = std::make_shared<engine::Sprite>(400, 200);
    slungus->loadGraphic("assets/images/slungus.png");
    add(slungus);

	const auto alphabet = std::make_shared<funkin::Alphabet>("SKIBIDI", 100, 500);
    add(alphabet);
}

void funkin::SongSelectState::update(const float delta) {
    funkin::MusicBeatState::update(delta);
    if (IsKeyPressed(KEY_RIGHT)) {
        selectedSong++;
        if (selectedSong >= static_cast<int8_t>(songs.size())) {
            selectedSong = 0;
        }
    } else if (IsKeyPressed(KEY_LEFT)) {
        selectedSong--;
        if (selectedSong < 0) {
            selectedSong = static_cast<int8_t>(songs.size() - 1);
        }
    }
    songText->text = songs[selectedSong];
    slungus->scale.x = static_cast<float>(sin(raylib::Window::GetTime())) + 2.0f;
    slungus->scale.y = static_cast<float>(cos(raylib::Window::GetTime())) + 2.0f;
    if (raylib::Keyboard::IsKeyPressed(KEY_ENTER)) {
        engine::Game::switchState(std::make_unique<funkin::PlayState>(songs[selectedSong], "hard"));
    }
}
