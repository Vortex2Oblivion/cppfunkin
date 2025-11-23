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

    std::string player1;
    std::string player2;
    std::string spectator;
    std::string stage;

    bool needsVoices = true;
    float scrollSpeed = 1.0f;
    float bpm = 60.0f;
};
class Song {
   public:
    static SongData parseChart(const std::string &songName, const std::string &difficulty);
    static SongData parseLegacy(const std::string &songName, const std::string &difficulty);
    static SongData parseVSlice(const std::string &songName, const std::string &difficulty);
};

}  // namespace funkin
