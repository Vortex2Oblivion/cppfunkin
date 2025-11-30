#include "song.hpp"

#include <fstream>
#include <iostream>
#include <raylib-cpp.hpp>

funkin::SongData funkin::Song::parseChart(const std::string& songName, const std::string& difficulty){
    const std::string folderPath = "assets/songs/"+songName;
    if(raylib::FileExists(folderPath + "/"+ songName + "-metadata.json")){
        return parseVSlice(songName, difficulty);
    }
    else if(raylib::FileExists(folderPath + "/" + difficulty + ".json")){
        return parseLegacy(songName, difficulty);
    }
    else{
        TraceLog(LOG_ERROR, ("Could not find chart file for song " + songName).c_str());
        throw std::runtime_error("Could not find chart file for song " + songName);
    }
    return {};
}

funkin::SongData funkin::Song::parseVSlice(const std::string& songName, const std::string& difficulty){
    const std::string basePath = "assets/songs/" + songName + "/";

    std::string chartPath = basePath + songName + "-chart.json";
    std::string metaPath = basePath + songName + "-metadata.json";

    std::ifstream chartFile(chartPath);
    nlohmann::json parsedChart = nlohmann::json::parse(chartFile);
    chartFile.close();

    std::ifstream metaFile(metaPath);
    nlohmann::json parsedMeta = nlohmann::json::parse(metaFile);
    metaFile.close();

    std::vector<NoteData> playerNotes = {};
    std::vector<NoteData> opponentNotes = {};

    for (auto note : parsedChart["notes"][difficulty]) {
        bool playerNote = note["d"] < 4;
        auto noteData = NoteData{
            .time = note["t"],
            .lane = static_cast<int>(note["d"]) % 4,
            .isPlayer = playerNote,
            .sustainLength = note["l"]
        };
        if (playerNote) {
            playerNotes.push_back(noteData);
        } else {
            opponentNotes.push_back(noteData);
        }
    }

    return {
        .parsedSong = parsedChart,
        .playerNotes = playerNotes,
        .opponentNotes = opponentNotes,
        .player1 = parsedMeta["playData"]["characters"]["player"],
        .player2 = parsedMeta["playData"]["characters"]["opponent"],
        .spectator = parsedMeta["playData"]["characters"]["girlfriend"],
        .stage = parsedMeta["playData"]["stage"],
        .needsVoices = true,
        .scrollSpeed = parsedChart["scrollSpeed"][difficulty],
        .bpm = parsedMeta["timeChanges"][0]["bpm"]
    };
}


funkin::SongData funkin::Song::parseLegacy(const std::string& songName, const std::string& difficulty) {
    std::string basePath = "assets/songs/" + songName + "/";
    std::ifstream chartFile(basePath + difficulty + ".json");
    nlohmann::json parsedChart = nlohmann::json::parse(chartFile);
    chartFile.close();

    nlohmann::json_abi_v3_12_0::json song;
    bool isPsychV1 = false;
    std::vector<NoteData> playerNotes = {};
    std::vector<NoteData> opponentNotes = {};

    if (parsedChart["song"].contains("song")) {
        song = parsedChart["song"];
    } else {
        song = parsedChart;
        isPsychV1 = true;
    }

    for (auto sectionNotes : song["notes"]) {
        for (auto sectionNote : sectionNotes["sectionNotes"]) {
            if (isPsychV1) {
                if (!sectionNotes["mustHitSection"]) {
                    if (sectionNote[1] > 3) {
                        sectionNote[1] = static_cast<int>(sectionNote[1]) % 4;
                    } else {
                        sectionNote[1] = static_cast<int>(sectionNote[1]) + 4;
                    }
                }
            }
            bool playerNote = (sectionNote[1] < 4) ? static_cast<bool>(sectionNotes["mustHitSection"]) : (!sectionNotes["mustHitSection"]);
            int lane = (static_cast<int>(sectionNote[1]) % 4) + (playerNote ? 0 : 4);
            auto noteData = NoteData{
                .time = static_cast<float>(sectionNote[0]),
                .lane = lane % 4,
                .isPlayer = playerNote,
                .sustainLength = static_cast<float>(sectionNote[2])
            };
            if (playerNote) {
                playerNotes.push_back(noteData);
            } else {
                opponentNotes.push_back(noteData);
            }
        }
    }

    std::string spectator = "gf";

    if (song.contains("spectator")) {
        spectator = song["spectator"];
    }
    else if (song.contains("gf")) {
        spectator = song["gf"];
    }
    else if (song.contains("gfVersion")) {
        spectator = song["gfVersion"];
    }
    else if (song.contains("player3")) {
        spectator = song["player3"];
    }

    return {
        .parsedSong = song,
        .playerNotes = playerNotes,
        .opponentNotes = opponentNotes,
        .player1 = song["player1"],
        .player2 = song["player2"],
        .spectator = spectator,
        .stage = song["stage"],
        .scrollSpeed = song["speed"],
        .bpm = song["bpm"]
    };
}