#pragma once

#include "conductor.hpp"
#include <state.hpp>

namespace funkin {
    class MusicBeatState : public engine::State {
        public:
            MusicBeatState();
            ~MusicBeatState() override;
            void create() override;
            void update(float delta) override;
            virtual void stepHit();
            virtual void beatHit();

        protected:
            std::shared_ptr<funkin::Conductor> conductor;

        private:
            bool forceConductorUpdate = true;
    };
}  // namespace funkin
