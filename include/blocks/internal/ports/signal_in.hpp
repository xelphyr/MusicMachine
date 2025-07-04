#pragma once
#include "blocks/internal/ports/port.hpp"
#include "blocks/internal/ports/signal_out.hpp"
#include <memory>
#include <SDL3/SDL.h>
#include <string>

namespace MM::BlockPort
{
    class SignalIn : public Port
    {
    public:
        /* *Offset* is the position relative to the center of the model when the model is facing left-to-right, range of -1 to +1 on both axes
        Tag is the ID of the input, aka what input the block expects at that port*/
        SignalIn(std::string tag, SDL_FPoint offset) {this->tag = tag; this->offset = offset;}
        ~SignalIn(){}

        void LinkPort() {}
        void NewFrame() {}

    private:
        std::weak_ptr<SignalOut> in;
    };
}