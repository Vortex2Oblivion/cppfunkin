#pragma once

#include <sparrowsprite.hpp>

namespace funkin {
	class AlphabetCharacter final : public engine::SparrowSprite {
		public:
			AlphabetCharacter(float x, float y, const char& character);
			~AlphabetCharacter() override;
};

}  // namespace funkin
