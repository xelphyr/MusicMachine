#pragma once
#include <unordered_map>
#include <string>
#include <SDL3/SDL.h>
#include <cassert>
#include <SDL3_Image/SDL_image.h>
#include "systems/render_context.hpp"

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

        SDL_Texture* GetTexture(std::string name) {if (TextureMap.find(name) != TextureMap.end()) return TextureMap[name]; else { SDL_Log("Texture not found: %s", name.c_str()); assert(false && "Texture not found"); return nullptr; }};

    private:
        TexManager()
        {
           LoadTexture("PulseSource");
           LoadTexture("ScalarSource");
           LoadTexture("SignalSource");

           LoadTexture("Drone");
           LoadTexture("Note");
        };
        void LoadTexture(std::string name)
        {
            SDL_Surface* surface = IMG_Load(("assets/blocks/"+name+".png").c_str());
            if (!surface) 
            {
                SDL_Log("Failed to load image: %s", SDL_GetError());
                assert(false && "Failed to load texture");
            }

            SDL_Texture* texture = SDL_CreateTextureFromSurface(RenderContext::Instance().renderer, surface);
            SDL_DestroySurface(surface);
            TextureMap[name] = texture;
        };
        ~TexManager(){};
        std::unordered_map<std::string, SDL_Texture*> TextureMap;
    };
}