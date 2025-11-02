#pragma once

#include "../engine/text.hpp"
#include "musicbeatstate.hpp"

namespace funkin {
class SongSelectState : public MusicBeatState {
   private:
    int selectedSong = 0;
    std::vector<std::string> songs = {};
    engine::Text* songText = nullptr;
    engine::Sprite* slungus = nullptr;

   public:
    SongSelectState(/* args */);
    ~SongSelectState() override;
    void update(float delta) override;
    void create() override;
};
}  // namespace funkin
