#include "alphabet.hpp"

#include <iostream>

funkin::Alphabet::Alphabet(const std::string& text, const float x, const float y) : engine::Group<funkin::AlphabetCharacter>(x, y) {
    uint16_t offset = 0;
    for (auto character : text) {
        const auto alphabetCharacter = std::make_shared<AlphabetCharacter>(offset * 44, 0, character);
        add(alphabetCharacter);
        offset++;
    }
}

funkin::Alphabet::~Alphabet() = default;