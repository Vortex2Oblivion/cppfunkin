#pragma once

#include <raylib-cpp.hpp>
#include <memory>
#include <vector>

namespace funkin {
    class Conductor {
    	friend class MusicBeatState;
		public:
	        explicit Conductor(const std::vector<std::shared_ptr<raylib::Music>> &tracks = {});
	        ~Conductor();
	        void start(std::vector<std::shared_ptr<raylib::Music>> tracks);
	        void start() const;
	        void stop() const;
	        void update(float delta);

	        [[nodiscard]] int getBeat() const;
	        [[nodiscard]] int getStep() const;
	        [[nodiscard]] float getCrochet() const;
	        [[nodiscard]] float getStepCrochet() const;

	        [[nodiscard]] float getMaxAudioTime() const;
	        [[nodiscard]] float getMinAudioTime() const;

	        std::vector<std::shared_ptr<raylib::Music>> tracks = {};
	        float time = -1.0f;
	        float bpm = 60.0f;
		private:
	        float lastAudioTime = 0.0f;
	        int step = 0;
	        int beat = 0;

	        bool didProperStepUpdate = false;
	        bool didProperBeatUpdate = false;

	        void updateStep();
	        void updateBeat();

	        void stepHit();
	        void beatHit();
    };
}  // namespace funkin
