#include "script.hpp"
#include <raylib-cpp.hpp>
#include <iostream>
#include <ostream>

funkin::Script::Script(const std::string &path) {
    this->path = path;
}

funkin::Script::~Script() {
    TraceLog(LOG_INFO, "SCRIPT: Shutting down Script...");
}