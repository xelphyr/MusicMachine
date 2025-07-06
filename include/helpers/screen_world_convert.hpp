#pragma once
#include "camera.hpp"

namespace MM::Helpers
{
    SDL_FPoint ScreenToWorld(SDL_FPoint screenPoint)
    {
        Camera& camera = Camera::Instance();
        SDL_FPoint worldPoint;

        float dx = (screenPoint.x - camera.dimensions.x / 2.f) / camera.zoom;
        float dy = (screenPoint.y - camera.dimensions.y / 2.f) / camera.zoom;

        worldPoint.x = camera.position.x + dx;
        worldPoint.y = camera.position.y - dy;  // flip Y

        return worldPoint;
    }

    SDL_FPoint WorldToScreen(SDL_FPoint worldPoint)
    {
        Camera& camera = Camera::Instance();
        SDL_FPoint screenPoint;

        float dx = (worldPoint.x - camera.position.x) * camera.zoom;
        float dy = (camera.position.y - worldPoint.y) * camera.zoom;

        screenPoint.x = dx + camera.dimensions.x / 2.f;
        screenPoint.y = dy + camera.dimensions.y / 2.f;

        return screenPoint;
    }

}