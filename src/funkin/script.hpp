#pragma once

#include <wrenbind17/wrenbind17.hpp>
#include <string>

namespace wren = wrenbind17;

namespace funkin {
    class Script {
        public:
            explicit Script(const std::string &path);
            ~Script();

            std::string path;
        private:
            wren::VM vm;
    };
}