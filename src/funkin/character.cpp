#include "character.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <utility>

#include "../engine/animatedsprite.hpp"

funkin::Character::Character(float x, float y, std::string characterName, funkin::CharacterType type) : SparrowSprite(x, y) {
    this->characterName = std::move(characterName);
    this->type = type;
    std::string characterBasePath = "assets/characters/" + this->characterName;
    std::ifstream characterFile(characterBasePath + "/character.json");

    if (characterFile.fail()) {
        switch (type) {
            case BF:
                this->characterName = "bf";
                break;
            case DAD:
                this->characterName = "dad";
                break;
            case GF:
                this->characterName = "gf";
                break;
        }
        characterBasePath = "assets/characters/" + this->characterName;
        characterFile = std::ifstream(characterBasePath + "/character.json");
    }

    auto parsedCharacter = nlohmann::json::parse(characterFile);
    characterFile.close();

    float scale = 1.0f;
    if (parsedCharacter.contains("scale")) {
        scale = parsedCharacter["scale"];
    }

    if (parsedCharacter.contains("globalOffset")) {
        position.x += static_cast<float>(parsedCharacter["globalOffset"]["x"]);
        position.y += static_cast<float>(parsedCharacter["globalOffset"]["y"]);
    }

    if (parsedCharacter.contains("cameraOffset")) {
        cameraOffset.x += static_cast<float>(parsedCharacter["cameraOffset"]["x"]);
        cameraOffset.y += static_cast<float>(parsedCharacter["cameraOffset"]["y"]);
    }

    loadGraphic(characterBasePath + "/spritesheet.png",
                characterBasePath + "/spritesheet.xml");

    for (auto animation : parsedCharacter["animations"]) {
        auto name = animation["name"];
        auto prefix = animation["prefix"];
        auto framerate = animation["framerate"];
        auto looped = animation["looped"];
        auto offset = animation["offset"];

        std::vector<uint8_t> indices = {};
        if (animation.contains("indices")) {
            indices = animation["indices"].get<std::vector<uint8_t>>();
        }

        addAnimation(name, prefix, framerate, indices, looped);
        this->offsets[name] = raylib::Vector2(offset["x"], offset["y"]);
    }
    this->scale.x = this->scale.y = scale;
    dance();
}

funkin::Character::~Character() = default;

void funkin::Character::dance() {
    if (hasAnimation("danceLeft")) {
        if (danceLeft) {
            playAnimation("danceLeft");
        } else {
            playAnimation("danceRight");
        }
        danceLeft = !danceLeft;
        return;
    }

    if (currentAnimation != nullptr && currentAnimation->animationTimer < 0.4f) {
        return;
    }

    playAnimation("idle");

}
