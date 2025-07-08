#pragma once

#include "blocks/internal/block.hpp"
#include "blocks/internal/ports/pulse_out.hpp"
#include "blocks/internal/ports/pulse_in.hpp"
#include "systems/noteframe_manager.hpp"
#include "helpers/gen_uuid.hpp"

namespace MM::Blocks
{
    class PulseSource : public Block
    {
    public:
        PulseSource();
        ~PulseSource(){};
        void Init() override;
        void Update() override;
        void Reset() override;
        std::vector<std::weak_ptr<Block>> Propagate() override;
        bool IsReady() override;
    private:
        std::shared_ptr<MM::BlockPort::PulseOut> output;
        Type m_type = Type::Source;
    };
}