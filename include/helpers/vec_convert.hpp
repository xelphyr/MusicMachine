#pragma once
#include <SDL3/SDL.h>
#include <imgui.h>

namespace MM::Helpers
{
    SDL_FPoint ToSDL_FPoint(ImVec2 point);

    ImVec2 ToImVec2(SDL_FPoint point);
}