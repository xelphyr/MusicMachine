#pragma once
#include "blocks/internal/ports/port.hpp"
#include "blocks/internal/ports/signal_in.hpp"
#include <memory>
#include <SDL3/SDL.h>
#include <string>

namespace MM::BlockPort
{
    class SignalOut : public Port
    {
    public:
        /* *Offset* is the position relative to the center of the model when the model is facing left-to-right, range of -1 to +1 on both axes
        Tag is the ID of the output, aka what output the user should expect at that port*/
        SignalOut(std::string tag, SDL_FPoint offset) {this->tag = tag; this->offset = offset;}
        ~SignalOut(){}

        void LinkPort() {}
        void NewFrame() {}

    private:
        std::weak_ptr<SignalIn> out;
    };
}