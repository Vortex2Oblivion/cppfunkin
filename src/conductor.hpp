#pragma once
#include <vector>
#include <raylib-cpp.hpp>

using namespace std;

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
        Conductor(vector<raylib::Music *> tracks);
        ~Conductor();
        void update(double delta);

        int getStep();
        double getCrochet();
        double getStepCrochet();

        vector<raylib::Music *> tracks;
        double time;
        double bpm;
    };
}