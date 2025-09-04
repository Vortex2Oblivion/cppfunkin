#include "musicbeatstate.hpp"
#include <iostream>

funkin::MusicBeatState::MusicBeatState() : State()
{
}

funkin::MusicBeatState::~MusicBeatState()
{
    delete conductor;
}

void funkin::MusicBeatState::update(float delta)
{
    funkin::State::update(delta);
    int lastStep = conductor->getStep();
    conductor->update(delta);
    if (lastStep != conductor->getStep())
    {
        stepHit();
    }
}

void funkin::MusicBeatState::stepHit()
{
    if (conductor->getStep() % 4 == 0)
    {
        beatHit();
    }
}

void funkin::MusicBeatState::beatHit()
{
}
