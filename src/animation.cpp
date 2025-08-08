#include "animation.hpp"

funkin::Animation::Animation(std::vector<funkin::Frame *> frames, int framerate)
{
    this->frames = frames;
    this->framerate = framerate;
}

funkin::Animation::~Animation()
{
}