#pragma once

#include <raylib-cpp.hpp>

namespace funkin
{
    class Camera : public raylib::Camera2D
    {
    private:
        /* data */
    public:
        Camera(/* args */);
        ~Camera();
        raylib::Vector2 position = raylib::Vector2();
        raylib::Vector2 cameraPosition = raylib::Vector2();
        Camera2D& BeginMode();
    };

} // namespace funkin
