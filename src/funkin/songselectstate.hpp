#pragma once

#include "musicbeatstate.hpp"
#include <text.hpp>

namespace funkin {
    class SongSelectState final : public funkin::MusicBeatState {
        public:
            SongSelectState(/* args */);
            ~SongSelectState() override;
            void update(float delta) override;
            void create() override;
        private:
            int8_t selectedSong = 0;
            std::vector<std::string> songs = {};
            std::shared_ptr<engine::Text> songText = nullptr;
            std::shared_ptr<engine::Sprite> slungus = nullptr;
    };
}  // namespace funkin
