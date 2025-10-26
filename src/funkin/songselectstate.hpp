#pragma once

#include "../engine/text.hpp"
#include "musicbeatstate.hpp"

namespace funkin {
class SongSelectState : public MusicBeatState {
   private:
    int selectedSong = 0;
    std::vector<std::string> songs;
    engine::Text* songText;
    engine::Sprite* slungus;

   public:
    SongSelectState(/* args */);
    virtual ~SongSelectState();
    virtual void update(float delta);
    virtual void create();
};
}  // namespace funkin
