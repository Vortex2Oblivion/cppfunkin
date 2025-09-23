#pragma once

#include <nlohmann/json.hpp>

namespace funkin
{
    class Song
    {
    public:
        static nlohmann::json_abi_v3_12_0::json parseChart(std::string songName, std::string difficulty);
    };

} // namespace funkin
