#include "camera.hpp"

engine::Camera::Camera() : raylib::Camera2D(raylib::Vector2(raylib::Window::GetWidth() / 2.0f, raylib::Window::GetHeight() / 2.0f),
                                            raylib::Vector2(raylib::Window::GetWidth() / 2.0f, raylib::Window::GetHeight() / 2.0f))
{
}

engine::Camera::~Camera()
{
}
raylib::Camera2D &engine::Camera::BeginMode()
{
    offset = Vector2Add(raylib::Vector2(raylib::Window::GetWidth() / 2.0f, raylib::Window::GetHeight() / 2.0f), position);
    target = Vector2Add(raylib::Vector2(raylib::Window::GetWidth() / 2.0f, raylib::Window::GetHeight() / 2.0f), cameraPosition);
    return raylib::Camera2D::BeginMode();
}
