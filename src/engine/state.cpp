#include "state.hpp"
#include <algorithm>

engine::State::State(/* args */) : Group(0, 0)
{
}

engine::State::~State()
{
}

void engine::State::create()
{
    initalized = true;
}