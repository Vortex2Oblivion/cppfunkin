#include "character.hpp"
#include "../engine/animatedsprite.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

funkin::Character::Character(float x, float y, std::string characterName) : SparrowSprite(x, y)
{

    std::string characterBasePath = "assets/characters/" + characterName;
    std::ifstream characterFile(characterBasePath + "/character.json");
    if (characterFile.fail())
    {
        characterBasePath = "assets/characters/bf";
        characterFile = std::ifstream(characterBasePath + "/character.json");
    }

    nlohmann::json parsedCharacter = nlohmann::json::parse(characterFile);
    characterFile.close();

    float scale = 1.0f;
    if (parsedCharacter.count("scale"))
    {
        scale = parsedCharacter["scale"];
    }

    if (parsedCharacter.count("globalOffset"))
    {
        position.x += (float)parsedCharacter["globalOffset"][0];
        position.y += (float)parsedCharacter["globalOffset"][1];
    }

    loadGraphic(characterBasePath + "/spritesheet.png", characterBasePath + "/spritesheet.xml");

    for (auto animation : parsedCharacter["animations"])
    {
        auto name = animation["name"];
        auto offsets = animation["offsets"];

        addAnimationByPrefix(name, animation["prefix"], animation["framerate"]);
        this->offsets[name] = raylib::Vector2(offsets[0], offsets[1]);
    }
    this->scale.x = this->scale.y = scale;

    playAnimation("idle");
}

funkin::Character::~Character()
{
    //engine::SparrowSprite::~SparrowSprite();
}

void funkin::Character::dance()
{
    if (!currentAnimation->isFinished())
    {
        return;
    }
    playAnimation("idle");
}
