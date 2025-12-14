#include "titlestate.hpp"

#include "mainmenustate.hpp"
#include "script.hpp"

#include <game.hpp>


funkin::TitleState::TitleState() : funkin::MusicBeatState() {}

funkin::TitleState::~TitleState() = default;

void funkin::TitleState::create() {
    funkin::MusicBeatState::create();

    introTextRaw = raylib::LoadFileText("assets/data/introText.txt");
    introText = raylib::TextSplit(introTextRaw, '\n');

    freakyMenu = std::make_shared<raylib::Music>("assets/music/freakyMenu.ogg");
    freakyMenu->looping = true;
    conductor->bpm = 102.0f;
    conductor->start({freakyMenu});

    const auto windowWidth = static_cast<float>(raylib::Window::GetWidth());
    const auto windowHeight = static_cast<float>(raylib::Window::GetHeight());

    gfDance = std::make_shared<engine::SparrowSprite>(windowWidth * 0.4f, windowHeight * 0.07f);
    gfDance->loadGraphic("assets/images/gfDanceTitle.png", "assets/images/gfDanceTitle.xml");
    gfDance->addAnimation("danceLeft", "gfDance", 24,  {30, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14});
    gfDance->addAnimation("danceRight", "gfDance", 24,  {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29});
    add(gfDance);

    logoBumpin = std::make_shared<engine::SparrowSprite>(-150.0f, -100.0f);
    logoBumpin->loadGraphic("assets/images/logoBumpin.png", "assets/images/logoBumpin.xml");
    logoBumpin->addAnimation("bump", "logo bumpin", 24);
    add(logoBumpin);

    titleText = std::make_shared<engine::SparrowSprite>(100, windowHeight * 0.8f);
    titleText->loadGraphic("assets/images/titleEnter.png", "assets/images/titleEnter.xml");
    titleText->addAnimation("idle", "Press Enter to Begin", 24, {}, true);
    titleText->playAnimation("idle");
    add(titleText);

    //const auto script = new funkin::Script("assets/scripts/script.wren");
    beatHit();
}

void funkin::TitleState::beatHit() {
    funkin::MusicBeatState::beatHit();
    logoBumpin->playAnimation("bump");
    gfDance->playAnimation(danceLeft ? "danceLeft" : "danceRight");
    danceLeft = !danceLeft;
}

void funkin::TitleState::update(const float delta) {
    funkin::MusicBeatState::update(delta);
    if (raylib::Keyboard::IsKeyPressed(KEY_ENTER)) {
        engine::Game::switchState(std::make_unique<funkin::MainMenuState>());
    }
}