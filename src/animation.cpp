#include "animation.hpp"
#include <iostream>

funkin::Animation::Animation(std::vector<funkin::Frame *> frames, int framerate)
{
    this->frames = frames;
    this->framerate = framerate;
    this->currentFrame = 0;
}

funkin::Animation::~Animation()
{
}

void funkin::Animation::update(double delta)
{
    frameTimer += delta;

    while (frameTimer >= 1.0 / (double)framerate)
    {
        frameTimer -= 1.0 / (double)framerate;
        if(currentFrame + 1 < frames.size()){
            currentFrame++;
        }
    }
}

void funkin::Animation::resetFrame(void) {
    currentFrame = 0;
    frameTimer = 0.0;
}