#include "character.hpp"

funkin::Character::Character(double x, double y, std::string charName) : SparrowSprite(x, y)
{
    if (charName == "defected")
    {
        loadGraphic("assets/images/defected.png", "assets/images/defected.xml");
        addAnimationByPrefix("idle", "defected idle", 24);
        addAnimationByPrefix("singDOWN", "defected down", 24);
        addAnimationByPrefix("singUP", "defected up", 24);
        addAnimationByPrefix("singRIGHT", "defected right", 24);
        addAnimationByPrefix("singLEFT", "defected left", 24);
    }

    if (charName == "bf")
    {
        loadGraphic("assets/images/BOYFRIEND.png", "assets/images/BOYFRIEND.xml");
        addAnimationByPrefix("idle", "BF idle dance", 24);
        addAnimationByPrefix("singDOWN", "BF NOTE DOWN0", 24);
        addAnimationByPrefix("singUP", "BF NOTE UP0", 24);
        addAnimationByPrefix("singRIGHT", "BF NOTE RIGHT0", 24);
        addAnimationByPrefix("singLEFT", "BF NOTE LEFT0", 24);
        offsets["idle"] = raylib::Vector2(-5, 0);
        offsets["singDOWN"] = raylib::Vector2(-20, -51);
        offsets["singUP"] = raylib::Vector2(-46, 27);
        offsets["singRIGHT"] = raylib::Vector2(-48, -7);
        offsets["singLEFT"] = raylib::Vector2(5, -6);
    }
    playAnimation("idle");
}

funkin::Character::~Character()
{
}