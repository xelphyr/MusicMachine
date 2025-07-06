#pragma once
#include <unordered_map>
#include <string>
#include <SDL3/SDL.h>

namespace MM::Systems
{
    class TexManager
    {
    public:
        static TexManager& Instance()
        {
            static TexManager t;
            return t;
        }

        TexManager(const TexManager&) = delete;
        TexManager& operator = (const TexManager&) = delete;

        SDL_Texture* GetTexture(std::string name) {return TextureMap[name];}

    private:
        TexManager(){};
        ~TexManager(){};
        std::unordered_map<std::string, SDL_Texture*> TextureMap;
    };
}