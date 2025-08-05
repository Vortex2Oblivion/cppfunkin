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
    }
}

void funkin::SparrowSprite::draw(){
    funkin::Sprite::draw();
    dest.width = source.width = 154;
    dest.height = source.height = 157;
    source.x = 223;
    source.y = 678;
}