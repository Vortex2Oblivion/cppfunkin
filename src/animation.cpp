#include "animation.hpp"
#include <iostream>

funkin::Animation::Animation(std::vector<funkin::Frame *> frames, int framerate)
{
    this->frames = frames;
    this->framerate = framerate;
}

funkin::Animation::~Animation()
{
}

void funkin::Animation::update(double delta)
{
    frameCounter++;

    if (frameCounter >= (GetFPS() / framerate))
    {
        frameCounter = 0;
        if(currentFrame + 1 < frames.size()){
            currentFrame++;
        }
    }
}