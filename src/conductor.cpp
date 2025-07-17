#include <vector>
#include <raylib-cpp.hpp>
#include <iostream>

#include "conductor.hpp"

using namespace std;


conductor::conductor(vector<raylib::Music *> tracks)
{
    this->tracks = tracks;
}

conductor::~conductor()
{
}

void conductor::update()
{
    for (auto track : tracks)
    {
        double resyncTimer = 0;
        if (track->GetTimePlayed() == _lastTime)
        {
            resyncTimer += GetFrameTime() * 0.001;
        }
        else
        {
            resyncTimer = 0;
        }
        time = track->GetTimePlayed() + resyncTimer;
        _lastTime = track->GetTimePlayed();
    }
    int oldStep = step;
    updateStep();
    updateBeat();
    if (oldStep != step)
    {
        stepHit();
    }
}

int conductor::getStep()
{
    return step;
}

double conductor::getCrochet()
{
    return (60.0 / bpm);
}

double conductor::getStepCrochet()
{
    return getCrochet() / 4;
}

void conductor::updateStep()
{
    step = floor(time / getStepCrochet());
}

void conductor::updateBeat()
{
    beat = floor(step / 4);
}

void conductor::stepHit()
{
    if (step % 4 == 0)
    {
        beatHit();
    }
}

void conductor::beatHit()
{
}