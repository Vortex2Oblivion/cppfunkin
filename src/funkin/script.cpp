#include "script.hpp"

#include <iostream>
#include <ostream>
#include <raylib-cpp.hpp>

funkin::Script::Script(const std::string &path) {
    this->path = path;

    wrenInitConfiguration(&config);

    config.writeFn = &writeFn;
    config.errorFn = &errorFn;

    vm = wrenNewVM(&config);

    result = wrenInterpret(vm, path.c_str(), raylib::LoadFileText(path).c_str());

    switch (result) {
        case WREN_RESULT_COMPILE_ERROR:
            TraceLog(LOG_ERROR, "SCRIPT: Compile Error!");
            break;
        case WREN_RESULT_RUNTIME_ERROR:
            TraceLog(LOG_ERROR, "SCRIPT: Runtime Error!");
            break;
        case WREN_RESULT_SUCCESS:
            TraceLog(LOG_INFO, "SCRIPT: Success!");
            break;
    }
}

funkin::Script::~Script() {
    TraceLog(LOG_INFO, "SCRIPT: Shutting down Script...");
    wrenFreeVM(vm);
}

void funkin::Script::writeFn(WrenVM* vm, const char *text) {
    std::cout << "INFO: SCRIPT: " << text;
}

void funkin::Script::errorFn(WrenVM* vm, const WrenErrorType errorType, const char* module, const int line, const char* msg) {
    switch (errorType) {
        case WREN_ERROR_COMPILE:
            TraceLog(LOG_ERROR, TextFormat("SCRIPT: [%s line %d] %s", module, line, msg));
            break;
        case WREN_ERROR_STACK_TRACE:
            TraceLog(LOG_ERROR, TextFormat("SCRIPT: [%s line %d] in %s", module, line, msg));
            break;
        case WREN_ERROR_RUNTIME:
            TraceLog(LOG_ERROR, TextFormat("SCRIPT: [Runtime Error] %s", msg));
            break;
    }
}

