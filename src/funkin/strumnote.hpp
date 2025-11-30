#pragma once

#include <sparrowsprite.hpp>

namespace funkin {

class StrumNote final : public engine::SparrowSprite {
	public:
		StrumNote(float x, float y, int lane);

		~StrumNote() override;
		void setPosition();

		int lane;
	};
}  // namespace funkin