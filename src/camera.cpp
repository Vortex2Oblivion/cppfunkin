#include "camera.hpp"

funkin::Camera::Camera() : raylib::Camera2D(raylib::Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f),
                                    raylib::Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f))
{
}

funkin::Camera::~Camera()
{
}
raylib::Camera2D& funkin::Camera::BeginMode()
{
    offset = Vector2Add(raylib::Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f), position);
    target = Vector2Add(raylib::Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f), cameraPosition);
    return raylib::Camera2D::BeginMode();
}
