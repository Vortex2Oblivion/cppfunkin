#pragma once

#include <string>
#include <wren.hpp>

namespace funkin {
    class Script {
        public:
            explicit Script(const std::string &path);
            ~Script();

            std::string path;
        private:
            WrenConfiguration config;
            WrenVM* vm;
            WrenInterpretResult result;
            static void writeFn(WrenVM* vm, const char * text);
            static void errorFn(WrenVM* vm, const WrenErrorType errorType, const char* module, int line, const char* msg);
    };
}