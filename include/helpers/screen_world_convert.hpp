#pragma once
#include "camera.hpp"

namespace MM::Helpers
{
    SDL_FPoint ScreenToWorld(SDL_FPoint screenPoint);

    SDL_FPoint WorldToScreen(SDL_FPoint worldPoint);

}