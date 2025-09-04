#pragma once
#include <vector>
#include <raylib-cpp.hpp>



namespace funkin
{
    class Conductor
    {
    private:
        float lastAudioTime = 0;
        int step = 0;
        int beat = 0;

        void updateStep();
        void updateBeat();

        void stepHit();
        void beatHit();

    public:
        Conductor();
        Conductor(std::vector<raylib::Music *> tracks);
        ~Conductor();
        void start(std::vector<raylib::Music *> tracks);
        void start();
        void update(float delta);

        int getBeat();
        int getStep();
        float getCrochet();
        float getStepCrochet();

        std::vector<raylib::Music *> tracks;
        float time = -1.0f;
        float bpm = 60.0f;
    };
}