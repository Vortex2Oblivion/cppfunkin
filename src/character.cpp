#include "character.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

funkin::Character::Character(double x, double y, std::string characterName) : SparrowSprite(x, y)
{

    std::string characterBasePath = "assets/characters/" + characterName;
    std::ifstream characterFile(characterBasePath + "/character.json");
    nlohmann::json parsedCharacter = nlohmann::json::parse(characterFile);
    characterFile.close();

    double scale = 1;
    if (parsedCharacter.count("scale"))
    {
        scale = parsedCharacter["scale"];
    }

    if (parsedCharacter.count("globalOffset"))
    {
        offset.x = parsedCharacter["globalOffset"][0];
        offset.y = parsedCharacter["globalOffset"][1];
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
}