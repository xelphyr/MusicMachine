#pragma once
#include <SDL3/SDL.h>

class Block
{
public:
    virtual ~Block() = default;

    virtual SDL_FPoint const GetPosition() {return position;}
    virtual bool const GetState() {return available;}
    virtual bool const GetOnTexture() {return on;}
    virtual bool const GetOffTexture() {return off;}

    virtual void SetPosition(SDL_FPoint newPos) {position = newPos;}
    virtual void Disable() {available = false;}
    virtual void Reset() {available = true;}
    virtual void SetOnTexture(SDL_Texture* newOn) {on = newOn;}
    virtual void SetOnTexture(SDL_Texture* newOff) {off = newOff;}
protected:
    SDL_FPoint position;
    SDL_Texture* off;
    SDL_Texture* on;
    bool available{true};
};