#pragma once

#include <vector>
#include <stack>
#include <unordered_map>
#include <memory>
#include "blocks/internal/block.hpp"
#include "blocks/internal/sprite/block_sprite.hpp"
#include "systems/event_bus.hpp"
#include "systems/sprite_manager.hpp"
#include "events/noteframe_event.hpp"
#include "events/add_block_event.hpp"
#include "events/remove_block_event.hpp"
#include "helpers/gen_uuid.hpp"

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

        void AddBlock(const AddBlockEvent& event);
        void RemoveBlock(const RemoveBlockEvent& event);

        void RunFrame(const NoteFrameEvent& event);
        void ResetFrame();
        void ProcessFrame();
    private:
        BlockManager()
        {
            EventBus::Instance().Subscribe<NoteFrameEvent>(
                [this](const NoteFrameEvent& e) { this->RunFrame(e); }
            );
            EventBus::Instance().Subscribe<AddBlockEvent>(
                [this](const AddBlockEvent& e) { this->AddBlock(e); }
            );
            EventBus::Instance().Subscribe<RemoveBlockEvent>(
                [this](const RemoveBlockEvent& e) { this->RemoveBlock(e); }
            );
        };
        ~BlockManager(){};
        std::unordered_map<std::string, std::shared_ptr<Block>> placedBlocks;
        std::vector<std::weak_ptr<Block>> sourceBlocks;
        std::unordered_map<std::shared_ptr<Block>, bool> blockProcessed;
        std::stack<std::shared_ptr<Block>> processStack;
    };
}
