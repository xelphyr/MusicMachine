#pragma once
#include <SDL3/SDL.h>
#include <imgui.h>

namespace MM::Helpers
{
    SDL_FPoint ToSDL_FPoint(ImVec2 point)
    {
        return SDL_FPoint({point.x, point.y});
    }

    ImVec2 ToImVec2(SDL_FPoint point)
    {
        return ImVec2({point.x, point.y});
    }
}