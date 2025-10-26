#include "character.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

#include "../engine/animatedsprite.hpp"

funkin::Character::Character(float x, float y, std::string characterName) : SparrowSprite(x, y) {
    this->characterName = characterName;
    std::string characterBasePath = "assets/characters/" + characterName;
    std::ifstream characterFile(characterBasePath + "/character.json");
    if (characterFile.fail()) {
        characterBasePath = "assets/characters/bf";
        characterFile = std::ifstream(characterBasePath + "/character.json");
    }

    nlohmann::json parsedCharacter = nlohmann::json::parse(characterFile);
    characterFile.close();

    float scale = 1.0f;
    if (parsedCharacter.count("scale")) {
        scale = parsedCharacter["scale"];
    }

    if (parsedCharacter.count("globalOffset")) {
        position.x += (float)parsedCharacter["globalOffset"]["x"];
        position.y += (float)parsedCharacter["globalOffset"]["y"];
    }

    loadGraphic(characterBasePath + "/spritesheet.png", characterBasePath + "/spritesheet.xml");

    for (auto animation : parsedCharacter["animations"]) {
        auto name = animation["name"];
        auto offset = animation["offset"];

        std::vector<uint8_t> indices = {};
        if (animation.contains("indices")) {
            indices = animation["indices"].get<std::vector<uint8_t>>();
        }

        addAnimation(name, animation["prefix"], animation["framerate"], indices);
        this->offsets[name] = raylib::Vector2(offset["x"], offset["y"]);
    }
    this->scale.x = this->scale.y = scale;

    if (characterName == "gf") {
        playAnimation("danceLeft");
    } else {
        playAnimation("idle");
    }
}

funkin::Character::~Character() {
    // engine::SparrowSprite::~SparrowSprite();
}

void funkin::Character::dance() {
    if (currentAnimation->animationTimer < 0.4f) {
        return;
    }
    if (characterName == "gf") {
        if (danceLeft) {
            playAnimation("danceLeft");
        } else {
            playAnimation("danceRight");
        }
        danceLeft = !danceLeft;
    } else {
        playAnimation("idle");
    }
}
