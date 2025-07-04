#pragma once
#include <unordered_map>
#include <string>
#include <SDL3/SDL.h>

namespace MM::Systems
{
    class TexManager
    {
    public:
        TexManager& Instance()
        {
            static TexManager t;
            return t;
        }

        TexManager(const TexManager&) = delete;
        TexManager& operator = (const TexManager&) = delete;

    private:
        TexManager(){};
        ~TexManager(){};
        std::unordered_map<std::string, SDL_Texture*> TextureMap;
    };
}