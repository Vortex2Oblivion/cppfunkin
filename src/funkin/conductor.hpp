#pragma once

#include <memory>
#include <raylib-cpp.hpp>
#include <vector>

namespace funkin {
class Conductor {
   private:
    float lastAudioTime = 0;
    int step = 0;
    int beat = 0;

    void updateStep();
    void updateBeat();

    void stepHit();
    void beatHit();

   public:
    explicit Conductor(const std::vector<std::shared_ptr<raylib::Music>> &tracks = {});
    ~Conductor();
    void start(std::vector<std::shared_ptr<raylib::Music>> tracks);
    void start() const;
    void stop() const;
    void update(float delta);

    [[nodiscard]] int getBeat() const;
    [[nodiscard]] int getStep() const;
    [[nodiscard]] float getCrochet() const;
    [[nodiscard]] float getStepCrochet() const;

    [[nodiscard]] float getMaxAudioTime() const;
    [[nodiscard]] float getMinAudioTime() const;

    std::vector<std::shared_ptr<raylib::Music>> tracks = {};
    float time = -1.0f;
    float bpm = 60.0f;
};
}  // namespace funkin