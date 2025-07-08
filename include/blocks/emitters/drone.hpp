#pragma once

#include "blocks/internal/block.hpp"
#include "blocks/internal/ports/pulse_in.hpp"
#include "blocks/internal/ports/signal_out.hpp"
#include "blocks/internal/ports/pulse_out.hpp"
#include "blocks/internal/ports/signal_in.hpp"

namespace MM::Blocks
{
    class Drone : public Block
    {
    public:
        Drone();
        ~Drone(){};
        void Init() override;
        void Update() override;
        void Reset() override;
        std::vector<std::weak_ptr<Block>> Propagate() override;
        bool IsReady() override;
    private:
        std::shared_ptr<MM::BlockPort::PulseIn> input;
        std::shared_ptr<MM::BlockPort::SignalOut> output;
        bool state = false; 
        Type m_type = Type::Emitter;

    };
}