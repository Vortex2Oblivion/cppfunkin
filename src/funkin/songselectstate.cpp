#include "songselectstate.hpp"
#include "playstate.hpp"
#include "../engine/game.hpp"

funkin::SongSelectState::SongSelectState()
{
    songText = new raylib::Text(songs[selectedSong], 20);
    songText->spacing = 1.0f;
}
funkin::SongSelectState::~SongSelectState()
{
}

void funkin::SongSelectState::update(float delta)
{
    if (IsKeyPressed(KEY_RIGHT))
    {
        selectedSong++;
        if (selectedSong >= (int)songs.size())
        {
            selectedSong = 0;
        }
    }
    if (IsKeyPressed(KEY_LEFT))
    {
        selectedSong--;
        if (selectedSong < 0)
        {
            selectedSong = (int)songs.size() - 1;
        }
    }
    songText->Draw(100, 100);
    songText->text = songs[selectedSong];
    if (IsKeyPressed(KEY_ENTER))
    {
        delete songText;
        engine::Game::switchState(new funkin::PlayState(songs[selectedSong], "hard"));
    }
}