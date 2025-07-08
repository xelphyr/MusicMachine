#pragma once

#include "camera.hpp"
#include "systems/render_context.hpp"

#include "blocks/internal/ports/pulse_in.hpp"
#include "blocks/internal/ports/pulse_out.hpp"

namespace MM::Blocks
{
    class Note : public Block
    {
    public:
        
    private: 

        MM::BlockPort::PulseIn input{"Input", {-1.f, 0.f}, this->shared_from_this()};
        MM::BlockPort::PulseOut output{"Output", {1.f, 0.f}, this->shared_from_this()};
    };
}