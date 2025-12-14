#include "script.hpp"

#include <sprite.hpp>
#include <raylib-cpp.hpp>

#include "game.hpp"
#include "playfield.hpp"


funkin::Script::Script(const std::string &path) {
    this->path = path;

    auto& raylib = vm.module("raylib");

    auto& vector2 = raylib.klass<raylib::Vector2>("Vector2");
    vector2.ctor<float, float>("new");

    
    auto& engine = vm.module("engine");

    auto& sprite = engine.klass<engine::Sprite>("Sprite");
    sprite.ctor<float, float>("new");
    sprite.func<&engine::Sprite::loadGraphic>("loadGraphic");
    sprite.func<&engine::Sprite::centerOrigin>("centerOrigin");
    sprite.func<&engine::Sprite::add>("add");
    sprite.var<&engine::Sprite::scale>("scale");

    auto& game = engine.klass<engine::Game>("Game");
    game.funcStatic<&engine::Game::add>("add");

    try {
        vm.runFromFile("main", path);

        auto mainClass = vm.find("main", "Main");
        auto main = mainClass.func("main()");

        auto res = main();
    }
    catch (wren::NotFound& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (wren::RuntimeError& e) {
        std::cerr << e.what() << std::endl;
    }

}

funkin::Script::~Script() {
    TraceLog(LOG_INFO, "SCRIPT: Shutting down Script...");
}