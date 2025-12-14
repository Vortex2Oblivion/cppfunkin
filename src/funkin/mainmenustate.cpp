#include "mainmenustate.hpp"

#include "coolutil.hpp"
#include "game.hpp"
#include "songselectstate.hpp"
#include "sparrowsprite.hpp"

funkin::MainMenuState::MainMenuState() : funkin::MusicBeatState() {}

funkin::MainMenuState::~MainMenuState() = default;

void funkin::MainMenuState::create() {
    funkin::MusicBeatState::create();
    menuBG = std::make_shared<engine::Sprite>();
    menuBG->loadGraphic("assets/images/menuBG.png");
    menuBG->scale = raylib::Vector2(1.1f, 1.1f);
    menuBG->screenCenter();
    menuBG->scrollFactor.y = 0.17f;
    add(menuBG);

    menuButtons = std::make_shared<engine::Group<engine::SparrowSprite>>();
    add(menuButtons);

    constexpr float spacing = 160.0f;
    const float top = (raylib::Window::GetSize().y - spacing * (static_cast<float>(menuItems.size()) - 1.0f)) / 2.0f;

    for (size_t i = 0; i < menuItems.size(); i++) {
        std::string item = menuItems[i];
        const auto menuButton = std::make_shared<engine::SparrowSprite>();
        menuButton->loadGraphic("assets/images/mainmenu/" + item + ".png", "assets/images/mainmenu/" + item + ".xml");
        menuButton->addAnimation("idle", item + " idle", 24, {}, true);
        menuButton->addAnimation("selected", item + " selected", 24, {}, true);
        menuButton->playAnimation("idle");
        menuButton->screenCenter(engine::Axes::X);
        menuButton->position.y = top + spacing * static_cast<float>(i);
        menuButton->scrollFactor.y = 0.4f;
        menuButton->ID = i;
        menuButtons->add(menuButton);
    }
    changeSelection(0);
}

void funkin::MainMenuState::update(const float delta) {
    funkin::MusicBeatState::update(delta);
    if (raylib::Keyboard::IsKeyPressed(KEY_UP)) {
        changeSelection(-1);
    }
    else if (raylib::Keyboard::IsKeyPressed(KEY_DOWN)) {
        changeSelection(1);
    }
    else if (raylib::Keyboard::IsKeyPressed(KEY_ENTER)) {
        switch (funkin::CoolUtil::str2int(menuItems[currentSelected])) {
            case funkin::CoolUtil::str2int("freeplay"):
                engine::Game::switchState(std::make_unique<funkin::SongSelectState>());
                break;
            default:
                break;
        }
    }

	if (alive) {
		engine::Game::defaultCamera->cameraPosition = engine::Game::defaultCamera->cameraPosition.Lerp(
			menuButtons->members[currentSelected]->getMidpoint(),
			1.0f - powf(1.0f - 0.06f, delta * 60.0f));
	}
}

void funkin::MainMenuState::changeSelection(const int8_t selection) {
    currentSelected = static_cast<uint8_t>(Wrap(static_cast<float>(currentSelected + selection), 0.0f, static_cast<float>(menuItems.size())));
    for (size_t i = 0; i < menuItems.size(); i++) {
        const auto menuButton = menuButtons->members[i];
        if (menuButton->ID == currentSelected && menuButton->currentAnimation->name == "idle") {
            menuButton->playAnimation("selected");
        }
        else if (menuButton->currentAnimation->name == "selected") {
            menuButton->playAnimation("idle");
        }
        menuButton->updateHitbox();
        menuButton->screenCenter(engine::Axes::X);
    }
}
