#pragma once

#include <animatedsprite.hpp>

namespace funkin {
	class HealthIcon final : public engine::AnimatedSprite {
		public:
			HealthIcon(const std::string& character, float x, float y);
			~HealthIcon() override;

			std::string character;
	};
}  // namespace funkin
