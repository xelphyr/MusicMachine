#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <memory>
#include "blocks/internal/block.hpp"

class Port
{
public:
    virtual ~Port() = default;
    std::weak_ptr<Block> GetParent();

protected:
    SDL_FPoint offset;
    std::weak_ptr<Block> parent;
    std::string tag;
    float val;
};