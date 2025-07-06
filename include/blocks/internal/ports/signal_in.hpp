#pragma once
#include "blocks/internal/ports/port_in.hpp"
#include "blocks/internal/ports/signal_out.hpp"
#include <memory>
#include <SDL3/SDL.h>
#include <string>

namespace MM::BlockPort
{
    class SignalIn : public PortIn
    {
    public:
        /* *Offset* is the position relative to the center of the model when the model is facing left-to-right, range of -1 to +1 on both axes
        Tag is the ID of the input, aka what input the block expects at that port*/
        SignalIn(std::string tag, SDL_FPoint offset, std::weak_ptr<Block> parent) {this->tag = tag; this->offset = offset; this->parent = parent;}
        ~SignalIn(){}

        void Receive(int value) {state = value;}
        bool isReady() override {return state>=0;}
        void Reset() override {state = -1;}

        void SetPort(std::weak_ptr<MM::BlockPort::SignalOut> newOut) {out = newOut;}
        void RemovePort() {out = std::weak_ptr<MM::BlockPort::SignalOut>();}
        std::weak_ptr<MM::BlockPort::SignalOut> GetPort() const {return out;}

        int GetState() const {return state;}

        PortType GetType() const override
        {
            return Port::SignalIn;
        }

    private:
        std::weak_ptr<MM::BlockPort::SignalOut> out;
        int state = -1;
    };
}