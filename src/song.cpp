#include "song.hpp"
#include <fstream>
#include <iostream>

nlohmann::json_abi_v3_12_0::json funkin::Song::parseChart(std::string songName, std::string difficulty)
{
    std::string basePath = "assets/songs/" + songName + "/";
    std::ifstream chartFile(basePath + difficulty + ".json");
    nlohmann::json parsedChart = nlohmann::json::parse(chartFile);
    chartFile.close();

    nlohmann::json_abi_v3_12_0::json song;

    if (parsedChart["song"].contains("song"))
    {
        song = parsedChart["song"];
    }
    else
    {
        song = parsedChart;
    }

    return song;
}