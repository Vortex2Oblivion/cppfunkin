#pragma once
#include <vector>
#include <raylib-cpp.hpp>

using namespace std;

class conductor
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
    conductor(vector<raylib::Music *> tracks);
    ~conductor();
    void update();

    int getStep();
    double getCrochet();
    double getStepCrochet();

    vector<raylib::Music *> tracks;
    double time;
    double bpm;
};