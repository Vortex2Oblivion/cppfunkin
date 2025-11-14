#pragma once
#include "../engine/sparrowsprite.hpp"
#include "musicbeatstate.hpp"

namespace funkin {
class TitleState final : public funkin::MusicBeatState {
   public:
    TitleState();
    ~TitleState() override;
    void create() override;
    void beatHit() override;
    void update(float delta) override;

    std::shared_ptr<engine::SparrowSprite> logoBumpin = nullptr;
    std::shared_ptr<engine::SparrowSprite> gfDance = nullptr;
    std::shared_ptr<engine::SparrowSprite> titleText = nullptr;

    std::shared_ptr<raylib::Music> freakyMenu = nullptr;
  protected:
    bool danceLeft = false;
};

}  // namespace funkin