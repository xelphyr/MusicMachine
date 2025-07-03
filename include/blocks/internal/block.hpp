#pragma once
#include <SDL3/SDL.h>

class Block
{
public:
    virtual ~Block() = default;

    virtual SDL_FPoint const GetPosition() {return position;}
    virtual bool const GetState() {return available;}

    virtual void SetPosition(SDL_FPoint newPos) {position = newPos;}
    virtual void Disable() {available = false;}
    virtual void Reset() {available = true;}
protected:
    SDL_FPoint position;
    bool available{true};
};