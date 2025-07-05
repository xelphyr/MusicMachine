#pragma once

#include <vector>
#include <stack>
#include <unordered_map>
#include <memory>
#include "blocks/internal/block.hpp"
#include "systems/event_bus.hpp"
#include "events/noteframe_event.hpp"

namespace MM::Systems
{
    class BlockManager
    {
    public:
        static BlockManager& Instance()
        {
            static BlockManager nfm;
            return nfm;
        }
        BlockManager(const BlockManager&) = delete;
        BlockManager& operator = (const BlockManager&) = delete;

        void RunFrame(const NoteFrameEvent& event);
        void ResetFrame();
        void ProcessFrame();
    private:
        BlockManager()
        {
            EventBus::Instance().Subscribe<NoteFrameEvent>
            (
                [this](const NoteFrameEvent& e) 
                {
                    this->RunFrame(e);
                }
            );
        };
        ~BlockManager(){};
        std::vector<std::shared_ptr<Block>> placedBlocks;
        std::vector<std::weak_ptr<Block>> sourceBlocks;
        std::unordered_map<std::shared_ptr<Block>, bool, BlockHash> blockProcessed;
        std::stack<std::shared_ptr<Block>> processStack;
    };
}
    