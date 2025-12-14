#pragma once

#include "camera.hpp"
#include "state.hpp"
#include "timer.hpp"
#include <script.hpp>

#include <memory>


namespace engine {
    class Game {
    public:
        explicit Game(std::unique_ptr<State> initialState);
        void update(float delta);
        static void switchState(std::unique_ptr<State> nextState);
        static std::vector<std::shared_ptr<engine::Camera>> cameras;
        static std::shared_ptr<engine::Camera> defaultCamera;
        static std::vector<engine::Timer> timers;
        static void add(const std::shared_ptr<engine::Object> &obj);

    private:
        static std::unique_ptr<engine::State> _state;
    };  // namespace engine
}
