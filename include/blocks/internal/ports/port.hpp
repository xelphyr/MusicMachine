#pragma once
#include <SDL3/SDL.h>
#include <string>

class Port
{
public:
    virtual ~Port() = default;
protected:
    SDL_FPoint offset;
    std::string tag;
    float val;
};