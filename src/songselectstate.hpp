#pragma once

#include "state.hpp"

namespace funkin
{
    class SongSelectState : public State
    {
    private:
        int selectedSong = 0;
        std::vector<std::string> songs = {"parasitic", "boxing-match-wg", "bitch"};
        raylib::Text *songText;

    public:
        SongSelectState(/* args */);
        virtual ~SongSelectState();
        virtual void update(double delta) override;
    };
}