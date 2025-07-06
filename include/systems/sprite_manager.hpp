#pragma once

#include "systems/block_manager.hpp"
#include "systems/render_context.hpp"
#include "blocks/internal/ports/port.hpp"
#include "helpers/screen_world_convert.hpp"
#include <SDL3/SDL.h>

namespace MM::Systems
{
    class SpriteManager
    {
    public:
        static SpriteManager& Instance()
        {
            static SpriteManager sm;
            return sm;
        }

        SpriteManager(const SpriteManager&) = delete;
        SpriteManager& operator = (const SpriteManager&) = delete;

        void Update();
        void Render();
        std::weak_ptr<BlockSprite> GetHoveredSprite(SDL_FPoint mousePos);
        std::weak_ptr<Port> GetHoveredPort(SDL_FPoint mousePos);

    private:
        SpriteManager() {};
        ~SpriteManager() {};
        std::unordered_map<std::string, std::weak_ptr<BlockSprite>> sprites;
        std::unordered_map<std::string, std::weak_ptr<Port>> ports;
    };
}