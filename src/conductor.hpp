#pragma once
#include <vector>
#include <raylib-cpp.hpp>



namespace funkin
{
    class Conductor
    {
    private:
        double lastAudioTime = 0;
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
        void update(double delta);

        int getStep();
        double getCrochet();
        double getStepCrochet();

        std::vector<raylib::Music *> tracks;
        double time = 0.0;
        double bpm = 60.0;
    };
}