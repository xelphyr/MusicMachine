#pragma once
#include "blocks/internal/ports/port_in.hpp"
#include "helpers/gen_uuid.hpp"
#include <memory>
#include <SDL3/SDL.h>
#include <string>

namespace MM::BlockPort {class PulseOut; }

namespace MM::BlockPort
{
    class PulseIn : public PortIn
    {
    public:
        /* *Offset* is the position relative to the center of the model when the model is facing left-to-right, range of -1 to +1 on both axes
        Tag is the ID of the input, aka what input the block expects at that port*/
        PulseIn(std::string tag, SDL_FPoint offset, std::weak_ptr<Block> parent) {this->tag = tag; this->offset = offset; this->parent = parent; this->id = MM::Helpers::generate_uuid();}
        ~PulseIn(){}

        void Receive(bool impulse) {state = impulse;}
        bool isReady() override {return state>=0;}
        void Reset() override {state = -1;}

        void SetPort(std::weak_ptr<MM::BlockPort::PulseOut> newOut) {out = newOut;}
        void RemovePort() {out = std::weak_ptr<MM::BlockPort::PulseOut>();}
        std::weak_ptr<MM::BlockPort::PulseOut> GetPort() const {return out;}
        int GetState() const {return state;}

        PortType GetType() const override
        {
            return Port::PulseIn;
        }
    private:
        std::weak_ptr<MM::BlockPort::PulseOut> out;
        int state = -1;
    };
}