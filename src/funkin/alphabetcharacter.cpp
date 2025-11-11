#include "alphabetcharacter.hpp"

#include "../engine/sparrowsprite.hpp"

#include <iostream>

funkin::AlphabetCharacter::AlphabetCharacter(const float x, const float y, const char &character) : engine::SparrowSprite(x, y) {
    loadGraphic("assets/images/alphabet.png", "assets/images/alphabet.xml");
    const auto characterString = std::string(1, character);
    addAnimation(characterString, characterString + " bold", 24, {}, true);
    playAnimation(characterString);
}

funkin::AlphabetCharacter::~AlphabetCharacter() = default;
