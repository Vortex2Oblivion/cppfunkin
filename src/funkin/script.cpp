#include "script.hpp"

#include <sprite.hpp>
#include <raylib-cpp.hpp>


funkin::Script::Script(const std::string &path) {
    this->path = path;
    
    auto& m = vm.module("engine");
    auto& cls = m.klass<engine::Sprite>("Sprite");
    cls.ctor<float, float>("new");
    cls.func<&engine::Sprite::loadGraphic>("loadGraphic");

    try {
        vm.runFromFile("main", path);

        auto mainClass = vm.find("main", "Main");
        auto main = mainClass.func("main()");

        auto res = main();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

}

funkin::Script::~Script() {
    TraceLog(LOG_INFO, "SCRIPT: Shutting down Script...");
}