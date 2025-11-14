#include "titlestate.hpp"

#include "../engine/game.hpp"
#include "songselectstate.hpp"

funkin::TitleState::TitleState() : funkin::MusicBeatState() {}

funkin::TitleState::~TitleState() = default;

void funkin::TitleState::create() {
    funkin::MusicBeatState::create();

    freakyMenu = std::make_shared<raylib::Music>("assets/music/freakyMenu.ogg");
    conductor->start({freakyMenu});
    conductor->bpm = 102.0f;

    gfDance = std::make_shared<engine::SparrowSprite>(raylib::Window::GetWidth() * 0.4f, raylib::Window::GetHeight() * 0.07f);
    gfDance->loadGraphic("assets/images/gfDanceTitle.png", "assets/images/gfDanceTitle.xml");
    gfDance->addAnimation("danceLeft", "gfDance", 24,  {30, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14});
    gfDance->addAnimation("danceRight", "gfDance", 24,  {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29});
    add(gfDance);

    logoBumpin = std::make_shared<engine::SparrowSprite>(-150.0f, -100.0f);
    logoBumpin->loadGraphic("assets/images/logoBumpin.png", "assets/images/logoBumpin.xml");
    logoBumpin->addAnimation("bump", "logo bumpin", 24);
    add(logoBumpin);

    titleText = std::make_shared<engine::SparrowSprite>(100, raylib::Window::GetHeight() * 0.8f);
    titleText->loadGraphic("assets/images/titleEnter.png", "assets/images/titleEnter.xml");
    titleText->addAnimation("idle", "Press Enter to Begin", 24, {}, true);
    titleText->playAnimation("idle");
    add(titleText);

    beatHit();
}

void funkin::TitleState::beatHit() {
    funkin::MusicBeatState::beatHit();
    logoBumpin->playAnimation("bump");
    if (danceLeft) {
        gfDance->playAnimation("danceLeft");
    }
    else {
        gfDance->playAnimation("danceRight");
    }
    danceLeft = !danceLeft;
}

void funkin::TitleState::update(const float delta) {
    funkin::MusicBeatState::update(delta);
    if (raylib::Keyboard::IsKeyPressed(KEY_ENTER)) {
        engine::Game::switchState(std::make_unique<funkin::SongSelectState>());
    }
}