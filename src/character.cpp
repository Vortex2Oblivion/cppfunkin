#include "character.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

funkin::Character::Character(double x, double y, std::string charName) : SparrowSprite(x, y)
{

    std::string characterBasePath = "assets/characters/" + charName;
    std::ifstream characterFile(characterBasePath + "/character.json");
    nlohmann::json parsedCharacter = nlohmann::json::parse(characterFile);
    characterFile.close();
    loadGraphic(characterBasePath + "/spritesheet.png", characterBasePath + "/spritesheet.xml");
    for (auto animation : parsedCharacter["animations"])
    {
        auto name = animation["name"];
        auto offsets = animation["offsets"];
        addAnimationByPrefix(name, animation["prefix"], animation["framerate"]);
        this->offsets[name] = raylib::Vector2(offsets[0], offsets[1]);
    }
    playAnimation("idle");
}

funkin::Character::~Character()
{
}