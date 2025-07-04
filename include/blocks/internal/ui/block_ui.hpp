#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class BlockUI
{
public:
    BlockUI(SDL_FPoint position, const char* pathToTexture, SDL_Renderer* renderer) 
    : position(position)
    {
        SDL_Surface* surface = IMG_Load(pathToTexture);
        if (!surface) 
        {
            SDL_Log("Failed to load image: %s", SDL_GetError());
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        overlay = texture;
    };
    ~BlockUI() {};

    SDL_FPoint const GetPosition() {return position;}
    bool const GetPower() {return powerStrength;}
    bool const GetOverlay() {return overlay;}

    void SetPosition(SDL_FPoint newPos) {position = newPos;}
    void SetPower(float newPower) {powerStrength = newPower;} 
    void SetOverlay(SDL_Texture* newOverlay) {overlay = newOverlay;}
protected:
    SDL_FPoint position;
    SDL_Texture* overlay;
    float powerStrength;
};