#pragma once
#include <vector>
#include <raylib-cpp.hpp>



namespace funkin
{
    class Conductor
    {
    private:
        double _lastTime;
        int step;
        int beat;

        void updateStep();
        void updateBeat();

        void stepHit();
        void beatHit();

    public:
        Conductor(std::vector<raylib::Music *> tracks);
        ~Conductor();
        void update(double delta);

        int getStep();
        double getCrochet();
        double getStepCrochet();

        std::vector<raylib::Music *> tracks;
        double time;
        double bpm;
    };
}