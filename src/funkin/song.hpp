#pragma once

#include <nlohmann/json.hpp>

namespace funkin {
struct NoteData {
    float time;
    int lane;
    bool isPlayer;
    float sustainLength;
};
struct SongData {
    nlohmann::json_abi_v3_12_0::json parsedSong = {};
    std::vector<NoteData> playerNotes = {};
    std::vector<NoteData> opponentNotes = {};
};
class Song {
   public:
    static SongData parseChart(const std::string &songName, const std::string &difficulty);
};

}  // namespace funkin
