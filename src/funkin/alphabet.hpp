#pragma once

#include "alphabetcharacter.hpp"
#include <group.hpp>
#include <array>

namespace funkin {
class Alphabet final : public engine::Group<funkin::AlphabetCharacter> {
   public:
    Alphabet(const std::string& text, float x, float y);
    ~Alphabet() override;
    // std::array<char, 26> characters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
    // 'v', 'w', 'x', 'y', 'z'};
};
}  // namespace funkin