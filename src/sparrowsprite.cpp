#include "sparrowsprite.hpp"

#include <pugixml.hpp>
#include <iostream>

funkin::SparrowSprite::SparrowSprite(double x, double y) : Sprite(x, y)
{
}

funkin::SparrowSprite::~SparrowSprite()
{
}

void funkin::SparrowSprite::loadGraphic(std::string imagePath, std::string xmlPath)
{
    funkin::Sprite::loadGraphic(imagePath);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("assets/images/notes.xml");

    for (auto frame : doc.child("TextureAtlas").children("SubTexture"))
    {
        std::cout << frame.attribute("name").as_string() << "\n";

        int x = frame.attribute("x").as_int();
        int y = frame.attribute("y").as_int();
        int width = frame.attribute("width").as_int();
        int height = frame.attribute("height").as_int();

        animations[frame.attribute("name").as_string()] =  raylib::Rectangle(x, y, width, height);
    }
}

void funkin::SparrowSprite::draw()
{
    funkin::Sprite::draw();
    source = animations["right confirm instance 10000"];
    dest.width = source.width;
    dest.height = source.height;
}