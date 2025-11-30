#pragma once

#include <sparrowsprite.hpp>

namespace funkin {

enum CharacterType { 
	BF, 
	DAD, 
	GF 
};

class Character final : public engine::SparrowSprite {
	protected:
		bool danceLeft = true;

	public:
		Character(float x, float y, std::string characterName, funkin::CharacterType type = DAD);

		~Character() override;
		void dance();

		std::string characterName;
		funkin::CharacterType type = DAD;
		raylib::Vector2 cameraOffset = raylib::Vector2::Zero();
	};
}  // namespace funkin