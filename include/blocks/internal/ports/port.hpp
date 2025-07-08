#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <memory>
#include "blocks/internal/block.hpp"

class Port
{
public:
    enum PortType
    {
        SignalIn,
        SignalOut,
        PulseIn,
        PulseOut,
        ScalarIn,
        ScalarOut
    };

    virtual ~Port() = default;
    std::weak_ptr<Block> GetParent() const {return parent;}
    SDL_FPoint GetOffset() const {return offset;}
    SDL_FPoint GetPosition() const
    {
        if (auto sp = parent.lock())
        {
            std::weak_ptr<BlockSprite> sprite = sp->GetSprite();
            if (auto s = sprite.lock())
            {
                SDL_FPoint pos = s->GetPosition();
                SDL_FPoint scale = s->GetScale();
                // Adjust position based on the offset
                return {pos.x + (scale.x/2) * offset.x, pos.y + (scale.x/2) * offset.y};
            }
        }
        return {0.f, 0.f}; // Default position if parent is not available
    }
    std::string GetTag() const {return tag;}
    std::string GetID() const {return id;}
    virtual PortType GetType() const = 0;

protected:
    SDL_FPoint offset;
    std::weak_ptr<Block> parent;
    std::string tag;
    std::string id;
};