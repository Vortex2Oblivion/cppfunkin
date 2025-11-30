#include "state.hpp"

engine::State::State() : Group(0, 0) {}

engine::State::~State() = default;

void engine::State::create() { initialized = true; }