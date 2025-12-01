#include "script.hpp"

#include <raylib-cpp.hpp>

funkin::Script::Script(const std::string &path) {
    this->path = path;
    const std::string code = raylib::LoadFileText(path);

    vm.runFromSource("main", code);
}

funkin::Script::~Script() {
    TraceLog(LOG_INFO, "SCRIPT: Shutting down Script...");
}