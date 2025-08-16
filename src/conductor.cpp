#include <vector>
#include <raylib-cpp.hpp>
#include <iostream>

#include "conductor.hpp"



funkin::Conductor::Conductor(std::vector<raylib::Music *> tracks)
{
    this->tracks = tracks;
}

funkin::Conductor::~Conductor()
{
}

void funkin::Conductor::update(double delta)
{
    if (!tracks.empty()) {
        auto track = tracks[0];
        if (track->GetTimePlayed() > time || time > track->GetTimePlayed() + 0.020)
        {
            time = track->GetTimePlayed();
        }
        else
        {
            time += delta;
        }
    }

    int oldStep = step;
    updateStep();
    updateBeat();
    if (oldStep != step)
    {
        stepHit();
    }
}

int funkin::Conductor::getStep()
{
    return step;
}

double funkin::Conductor::getCrochet()
{
    return (60.0 / bpm);
}

double funkin::Conductor::getStepCrochet()
{
    return getCrochet() / 4;
}

void funkin::Conductor::updateStep()
{
    step = floor(time / getStepCrochet());
}

void funkin::Conductor::updateBeat()
{
    beat = floor(step / 4);
}

void funkin::Conductor::stepHit()
{
    if (step % 4 == 0)
    {
        beatHit();
    }
}

void funkin::Conductor::beatHit()
{
}