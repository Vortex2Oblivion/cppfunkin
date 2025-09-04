#include "animation.hpp"
#include <iostream>

funkin::Animation::Animation(std::vector<funkin::Frame *> frames, uint8_t framerate)
{
    this->frames = frames;
    this->framerate = framerate;
    this->currentFrame = 0;
}

funkin::Animation::~Animation()
{
}

void funkin::Animation::update(float delta)
{
    frameTimer += delta;

    while (frameTimer >= 1.0f / framerate)
    {
        frameTimer -= 1.0f / framerate;
        if (currentFrame + 1 < frames.size())
        {
            currentFrame++;
        }
    }
}

void funkin::Animation::resetFrame()
{
    currentFrame = 0;
    frameTimer = 0.0;
}

bool funkin::Animation::isFinished()
{
    return currentFrame + 1 >= frames.size();
}