#pragma once

#include "../engine/text.hpp"
#include "musicbeatstate.hpp"

namespace funkin {
class SongSelectState final : public MusicBeatState {
   private:
    int selectedSong = 0;
    std::vector<std::string> songs = {};
    std::shared_ptr<engine::Text> songText = nullptr;
    std::shared_ptr<engine::Sprite> slungus = nullptr;

   public:
    SongSelectState(/* args */);
    ~SongSelectState() override;
    void update(float delta) override;
    void create() override;
};
}  // namespace funkin
