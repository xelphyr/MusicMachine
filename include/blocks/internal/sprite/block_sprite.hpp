#pragma once
#include "systems/tex_manager.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class BlockSprite
{
public:
    BlockSprite(SDL_FPoint position, SDL_FPoint scale, std::string spriteName) 
    : position(position), scale(scale), powerStrength(0.0f), overlay(nullptr)
    {
        overlay = MM::Systems::TexManager::Instance().GetTexture(spriteName);
    };
    ~BlockSprite() {};

    SDL_FPoint const GetPosition() {return position;}
    SDL_FPoint const GetScale() {return scale;}
    bool const GetPower() {return powerStrength;}
    SDL_Texture* const GetOverlay() {return overlay;}

    void SetPosition(SDL_FPoint newPos) {position = newPos;}
    void SetPower(float newPower) {powerStrength = newPower;} 
    void SetOverlay(SDL_Texture* newOverlay) {overlay = newOverlay;}
protected:
    SDL_FPoint position;
    SDL_FPoint scale;
    SDL_Texture* overlay;
    float powerStrength;
};