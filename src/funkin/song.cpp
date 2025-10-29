#include "song.hpp"

#include <fstream>
#include <iostream>

funkin::SongData funkin::Song::parseChart(std::string songName, std::string difficulty) {
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
                        sectionNote[1] = (int)sectionNote[1] % 4;
                    } else {
                        sectionNote[1] = (int)sectionNote[1] + 4;
                    }
                }
            }
            bool playerNote = (sectionNote[1] < 4) ? (bool)(sectionNotes["mustHitSection"]) : (!sectionNotes["mustHitSection"]);
            int lane = ((int)sectionNote[1] % 4) + (playerNote ? 0 : 4);
            NoteData noteData = NoteData{
                .time = (float)sectionNote[0] / 1000.0f,
                .lane = lane % 4,
                .isPlayer = playerNote,
                .sustainLength = (float)sectionNote[2] / 1000.0f
            };
            if (playerNote) {
                playerNotes.push_back(noteData);
            } else {
                opponentNotes.push_back(noteData);
            }
        }
    }
    return {
        .parsedSong = song,
        .playerNotes = playerNotes,
        .opponentNotes = opponentNotes,
    };
}