#pragma once
#include <SDL3/SDL.h>

namespace MM::Helpers
{
    inline SDL_FPoint operator+=(SDL_FPoint& lhs, SDL_FPoint rhs)
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        return lhs;
    }

    inline SDL_FPoint operator-=(SDL_FPoint& lhs, SDL_FPoint rhs)
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        return lhs;
    }

    inline SDL_FPoint operator+(SDL_FPoint lhs, SDL_FPoint rhs)
    {
        return SDL_FPoint({lhs.x + rhs.x, lhs.y + rhs.y});
    }

    inline SDL_FPoint operator-(SDL_FPoint lhs, SDL_FPoint rhs)
    {
        return SDL_FPoint({lhs.x - rhs.x, lhs.y - rhs.y});
    }

    inline SDL_FPoint operator/(SDL_FPoint lhs, float rhs)
    {
        return SDL_FPoint({lhs.x / rhs, lhs.y / rhs});
    }

    inline SDL_FPoint operator*(SDL_FPoint lhs, float rhs)
    {
        return SDL_FPoint({lhs.x * rhs, lhs.y * rhs});
    }
}