#pragma once

#include <nlohmann/json.hpp>

namespace funkin
{
    struct NoteData
    {
        float time;
        int lane;
        bool isPlayer;
    };
    struct SongData
    {
        nlohmann::json_abi_v3_12_0::json parsedSong;
        std::vector<NoteData> notes;
        unsigned int playerNotes;
    };
    class Song
    {
    public:
        static SongData parseChart(std::string songName, std::string difficulty);
    };

} // namespace funkin
