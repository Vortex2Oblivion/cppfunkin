#include "stage.hpp"

#include <fstream>
#include <iostream>

funkin::Stage::Stage(std::string name, funkin::Character* boyfriend, funkin::Character* dad, float x, float y) : engine::Group<engine::Object>(x, y) {
    this->name = name;
    std::string path = "assets/stages/" + name + "/";
    if (!raylib::FileExists(path)) {
        path = "assets/stages/stage/";
    }

    std::ifstream stageFile = std::ifstream(path + "stage.json");
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

        std::string imageFile = path + (std::string)object["file"] + extension;

        if (!raylib::FileExists(imageFile)) {
            std::cerr << "Could not find image at path: " << imageFile << "\n";
            continue;
        }

        auto position = object["position"];

        engine::Sprite* stageObject = new engine::Sprite(position["x"], position["y"]);
        stageObject->loadGraphic(imageFile);

        if (object.count("scale")) {
            auto scale = object["scale"];
            stageObject->scale = raylib::Vector2(scale["x"], scale["y"]);
        }

        stageObject->centerOrigin();
        add(stageObject);
    }

    auto dadPosition = parsedStage["characters"]["dad"];
    auto boyfriendPosition = parsedStage["characters"]["boyfriend"];
    dad->position += raylib::Vector2(dadPosition["x"], dadPosition["y"]);
    boyfriend->position += raylib::Vector2(boyfriendPosition["x"], boyfriendPosition["y"]);

    add(dad);
    add(boyfriend);
}

funkin::Stage::~Stage() {}