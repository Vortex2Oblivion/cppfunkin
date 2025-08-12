#include "songselectstate.hpp"
#include "game.hpp"
#include "playstate.hpp"

funkin::SongSelectState::SongSelectState()
{
    songText = new raylib::Text(songs[selectedSong], 20);
    songText->spacing = 1.0f;
}
funkin::SongSelectState::~SongSelectState()
{
}

void funkin::SongSelectState::update(double delta)
{
    songText->Draw(100, 100);
    songText->text = songs[selectedSong];
    if (IsKeyPressed(KEY_RIGHT))
    {
        selectedSong++;
        if (selectedSong >= songs.size())
        {
            selectedSong = 0;
        }
    }
    if (IsKeyPressed(KEY_LEFT))
    {
        selectedSong--;
        if (selectedSong < 0)
        {
            selectedSong = songs.size() - 1;
        }
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        funkin::Game::switchState(new funkin::PlayState(songs[selectedSong], "hard"));
        delete songText;
    }
}