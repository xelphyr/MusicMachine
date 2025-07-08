#pragma once
#include "blocks/internal/ports/port_out.hpp"
#include "helpers/gen_uuid.hpp"
#include <memory>
#include <SDL3/SDL.h>
#include <string>

namespace MM::BlockPort { class ScalarIn; }

namespace MM::BlockPort
{
    class ScalarOut : public PortOut
    {
    public:
        /* *Offset* is the position relative to the center of the model when the model is facing left-to-right, range of -1 to +1 on both axes
        Tag is the ID of the output, aka what output the user should expect at that port*/
        ScalarOut(std::string tag, SDL_FPoint offset, std::weak_ptr<Block> parent) {this->tag = tag; this->offset = offset; this->parent = parent; this->id = MM::Helpers::generate_uuid();}
        ~ScalarOut(){}

        void SetState(float value) {state = value;}
        void Send();
        void Reset() override {}

        void SetPort(std::weak_ptr<MM::BlockPort::ScalarIn> newIn) {in = newIn;}
        void RemovePort() {in = std::weak_ptr<MM::BlockPort::ScalarIn>();}
        std::weak_ptr<MM::BlockPort::ScalarIn> GetPort() const {return in;}

        PortType GetType() const override
        {
            return Port::ScalarOut;
        }

    private:
        std::weak_ptr<MM::BlockPort::ScalarIn> in;
        float state = -1.f; // Default state for scalar output, can be modified as needed
    };
}