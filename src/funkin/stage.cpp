#include "stage.hpp"

#include <fstream>
#include <iostream>

funkin::Stage::Stage(const std::string& name, std::shared_ptr<funkin::Character> boyfriend, std::shared_ptr<funkin::Character> dad, std::shared_ptr<funkin::Character> girlfriend, float x, float y)
    : engine::Group<engine::Object>(x, y) {
    this->name = name;
    std::string path = "assets/stages/" + name + "/";
    if (!raylib::FileExists(path)) {
        path = "assets/stages/stage/";
    }

    auto stageFile = std::ifstream(path + "stage.json");
    parsedStage = nlohmann::json::parse(stageFile);
    stageFile.close();

    if (parsedStage.contains("zoom")) {
        zoom = parsedStage["zoom"];
    }

    for (auto object : parsedStage["objects"]) {
        std::string extension = ".png";

        if (object.contains("extension")) {
            extension = object["extension"];
        }

        std::string imageFile = path + static_cast<std::string>(object["file"]) += extension;

        if (!raylib::FileExists(imageFile)) {
            std::cerr << "Could not find image at path: " << imageFile << "\n";
            continue;
        }

        auto position = object["position"];

        auto stageObject = std::make_shared<engine::Sprite>(position["x"], position["y"]);
        stageObject->loadGraphic(imageFile);

        if (object.count("scale")) {
            auto scale = object["scale"];
            stageObject->scale = raylib::Vector2(scale["x"], scale["y"]);
        }

        if (object.count("scrollFactor")) {
            auto scrollFactor = object["scrollFactor"];
            stageObject->scrollFactor = raylib::Vector2(scrollFactor["x"], scrollFactor["y"]);
        }

        stageObject->centerOrigin();
        add(stageObject);
    }

    auto characters = parsedStage["characters"];

    auto girlfriendData = characters["girlfriend"];
    auto dadData = characters["dad"];
    auto boyfriendData = characters["boyfriend"];

    // required data
    auto girlfriendPosition = characters["girlfriend"]["position"];
    auto dadPosition = characters["dad"]["position"];
    auto boyfriendPosition = characters["boyfriend"]["position"];

    girlfriend->position += raylib::Vector2(girlfriendPosition["x"], girlfriendPosition["y"]);
    dad->position += raylib::Vector2(dadPosition["x"], dadPosition["y"]);
    boyfriend->position += raylib::Vector2(boyfriendPosition["x"], boyfriendPosition["y"]);

    // optional data (camera offset, scroll, etc)
    if (boyfriendData.contains("cameraOffset")){
        boyfriend->cameraOffset += raylib::Vector2(boyfriendData["cameraOffset"]["x"], boyfriendData["cameraOffset"]["y"]);
    }

    if (dadData.contains("cameraOffset")){
        dad->cameraOffset += raylib::Vector2(dadData["cameraOffset"]["x"], dadData["cameraOffset"]["y"]);
    }

    if (girlfriendData.contains("cameraOffset")){
        girlfriend->cameraOffset += raylib::Vector2(girlfriendData["cameraOffset"]["x"], girlfriendData["cameraOffset"]["y"]);
    }

    if (boyfriendData.contains("scrollFactor")){
        boyfriend->scrollFactor = raylib::Vector2(boyfriendData["scrollFactor"]["x"], boyfriendData["scrollFactor"]["y"]);
    }

    if (dadData.contains("scrollFactor")){
        dad->scrollFactor = raylib::Vector2(dadData["scrollFactor"]["x"], dadData["scrollFactor"]["y"]);
    }

    if (girlfriendData.contains("scrollFactor")){
        girlfriend->scrollFactor = raylib::Vector2(girlfriendData["scrollFactor"]["x"], girlfriendData["scrollFactor"]["y"]);
    }

    add(girlfriend);
    add(dad);
    add(boyfriend);
}

funkin::Stage::~Stage() = default;