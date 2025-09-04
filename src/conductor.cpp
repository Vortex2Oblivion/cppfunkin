#include <vector>
#include <raylib-cpp.hpp>

#include "conductor.hpp"

funkin::Conductor::Conductor()
{
    this->tracks = {};
}

funkin::Conductor::Conductor(std::vector<raylib::Music *> tracks)
{
    this->tracks = tracks;
}

funkin::Conductor::~Conductor()
{
    if (tracks.empty())
    {
        return;
    }
    for (auto track : tracks)
    {
        track->Stop();
        delete track;
    }
}

void funkin::Conductor::start(std::vector<raylib::Music *> tracks)
{
    this->tracks = tracks;
    start();
}

void funkin::Conductor::start()
{
    if (tracks.empty())
    {
        return;
    }
    for (auto track : tracks)
    {
        track->Play();
    }
}

void funkin::Conductor::update(float delta)
{
    if (!tracks.empty())
    {
        auto track = tracks[0];
        if (track->GetTimePlayed() != lastAudioTime)
        {
            time = track->GetTimePlayed();
        }
        else
        {
            time += delta;
        }
        lastAudioTime = track->GetTimePlayed();
    }

    int oldStep = step;
    updateStep();
    updateBeat();
    if (oldStep != step)
    {
        stepHit();
    }
}

int funkin::Conductor::getBeat()
{
    return beat;
}

int funkin::Conductor::getStep()
{
    return step;
}

float funkin::Conductor::getCrochet()
{
    return (60.0f / bpm);
}

float funkin::Conductor::getStepCrochet()
{
    return getCrochet() / 4;
}

void funkin::Conductor::updateStep()
{
    step = (int)(time / getStepCrochet());
}

void funkin::Conductor::updateBeat()
{
    beat = (int)(step / 4);
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