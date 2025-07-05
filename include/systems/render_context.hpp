#pragma once

#include <SDL3/SDL.h>

namespace MM::Systems
{
    struct RenderContext
    {
    public:
        static RenderContext& Instance()
        {
            static RenderContext rc;
            return rc;
        }

        RenderContext(const RenderContext&) = delete;
        RenderContext& operator = (const RenderContext&) = delete;
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* texture = nullptr;
    private:
        RenderContext(){};
    };

}
    