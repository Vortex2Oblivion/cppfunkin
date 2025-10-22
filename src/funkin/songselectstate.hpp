#pragma once

#include "../engine/text.hpp"
#include "musicbeatstate.hpp"

namespace funkin {
class SongSelectState : public MusicBeatState {
   private:
    int selectedSong = 0;
    std::vector<std::string> songs = {
        "dad-battle", "ziplash", "decoded", "parasitic", "boxing-match-wg", "bitch", "goktrap", "catshitdotmp3", "bonedoggle", "shitton-of-notes"};
    engine::Text* songText;

   public:
    SongSelectState(/* args */);
    virtual ~SongSelectState();
    virtual void update(float delta);
    virtual void create();
};
}  // namespace funkin