#pragma once

#include "camera.hpp"
#include "state.hpp"
#include "timer.hpp"

#include <memory>

namespace engine {
    class Game {
    private:
        static std::unique_ptr<engine::State> _state;

    public:
        explicit Game(std::unique_ptr<State> initialState);
        void update(float delta);
        static void switchState(std::unique_ptr<State> nextState);
        static std::vector<std::shared_ptr<engine::Camera>> cameras;
        static std::shared_ptr<engine::Camera> defaultCamera;
        static std::vector<engine::Timer> timers;

    };  // namespace engine
}