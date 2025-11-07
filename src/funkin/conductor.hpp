#pragma once

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
    explicit Conductor(const std::vector<raylib::Music*> &tracks = {});
    ~Conductor();
    void start(std::vector<raylib::Music*> tracks);
    void start();
    void stop();
    void update(float delta);

    int getBeat() const;
    int getStep() const;
    float getCrochet() const;
    float getStepCrochet() const;

    float getMaxAudioTime() const;
    float getMinAudioTime() const;

    std::vector<raylib::Music*> tracks = {};
    float time = -1.0f;
    float bpm = 60.0f;
};
}  // namespace funkin