#pragma once
#include "blocks/internal/ports/port_out.hpp"
#include "blocks/internal/ports/pulse_in.hpp"
#include <memory>
#include <SDL3/SDL.h>
#include <string>

namespace MM::BlockPort
{
    class PulseOut : public PortOut
    {
    public:
        /* *Offset* is the position relative to the center of the model when the model is facing left-to-right, range of -1 to +1 on both axes
        Tag is the ID of the output, aka what output the user should expect at that port*/
        PulseOut(std::string tag, SDL_FPoint offset, std::weak_ptr<Block> parent) {this->tag = tag; this->offset = offset; this->parent = parent;}
        ~PulseOut(){}

        void SetState() {state = true;}
        void Send() {if (auto sp = in.lock())sp->Receive(state); state = false;}
        void Reset() override {state = false;}

        void SetPort(std::weak_ptr<MM::BlockPort::PulseIn> newIn) {in = newIn;}
        void RemovePort() {in = std::weak_ptr<MM::BlockPort::PulseIn>();}
        std::weak_ptr<MM::BlockPort::PulseIn> GetPort() const {return in;}

        PortType GetType() const override
        {
            return Port::PulseOut;
        }
    private:
        std::weak_ptr<MM::BlockPort::PulseIn> in;
        bool state = false;

    };
}