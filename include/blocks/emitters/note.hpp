#pragma once

#include "blocks/internal/logic/note.hpp"
#include "blocks/internal/ui/block_ui.hpp"
#include "blocks/internal/ports/pulse_in.hpp"
#include "blocks/internal/ports/pulse_out.hpp"

namespace MM::Blocks
{
    class Note
    {
    public: 
        NoteLogic logic;
        BlockUI ui{};
        MM::BlockPort::PulseIn input{"Input", {-1.f, 0.f}};
        MM::BlockPort::PulseOut output{"Output", {1.f, 0.f}};
    };
}