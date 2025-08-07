#include "animation.hpp"

funkin::Animation::Animation(std::vector<funkin::Frame *> frames)
{
    this->frames = frames;
}

funkin::Animation::~Animation()
{
}