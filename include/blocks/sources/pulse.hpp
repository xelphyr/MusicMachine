#pragma once

#include "blocks/internal/block.hpp"
#include "blocks/internal/ports/pulse_out.hpp"
#include "systems/noteframe_manager.hpp"

namespace MM::Blocks
{
    class Pulse : public Block
    {
    public:
        Pulse();
        ~Pulse(){};
        void Update() override;
        void Reset() override;
        std::vector<std::weak_ptr<Block>> Propagate() override;
        bool IsReady() override;
    private:
        std::shared_ptr<MM::BlockPort::PulseOut> output;
    };
}