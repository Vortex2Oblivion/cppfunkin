#pragma once

#include <array>

#include "musicbeatstate.hpp"
#include "sparrowsprite.hpp"
#include "sprite.hpp"

namespace funkin {
    class MainMenuState : public funkin::MusicBeatState {
        public:
            MainMenuState();
            ~MainMenuState() override;
            void create() override;
            void update(float delta) override;

            std::shared_ptr<engine::Sprite> menuBG = nullptr;
            std::shared_ptr<engine::Group<engine::SparrowSprite>> menuButtons = nullptr;
            std::array<std::string, 3> menuItems = {"storymode", "freeplay", "options"};

        protected:
            uint8_t currentSelected = 0;
            void changeSelection(int8_t selection);
    };
} // funkin