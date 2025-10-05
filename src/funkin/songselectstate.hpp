#pragma once

#include "musicbeatstate.hpp"
#include "../engine/text.hpp"

namespace funkin
{
    class SongSelectState : public MusicBeatState
    {
    private:
        int selectedSong = 0;
        std::vector<std::string> songs = { "dad-battle", "ziplash", "decoded", "parasitic", "boxing-match-wg", "bitch", "goktrap", "catshitdotmp3"};
        engine::Text *songText;

    public:
        SongSelectState(/* args */);
        virtual ~SongSelectState();
        virtual void update(float delta) override;
    };
}