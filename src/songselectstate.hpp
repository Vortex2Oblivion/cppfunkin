#pragma once

#include "state.hpp"

namespace funkin
{
    class SongSelectState : public State
    {
    private:
        int selectedSong = 0;
        std::vector<std::string> songs = {"dad-battle", "decoded", "parasitic", "boxing-match-wg", /*"bitch",*/ "goktrap", "catshitdotmp3"};
        raylib::Text *songText;

    public:
        SongSelectState(/* args */);
        virtual ~SongSelectState();
        virtual void update(float delta) override;
    };
}