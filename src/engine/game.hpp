#pragma once
#include "camera.hpp"
#include "state.hpp"

#include <memory>

namespace engine {
class Game {
   private:
    static std::unique_ptr<engine::State> _state;

   public:
    explicit Game(std::unique_ptr<State> initialState);
    void update(float delta);
    static void switchState(std::unique_ptr<State> nextState);
    static std::vector<engine::Camera*> cameras;
    static engine::Camera* defaultCamera;
};

}  // namespace engine