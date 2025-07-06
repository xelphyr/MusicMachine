#pragma once

#include <vector>
#include <stack>
#include <unordered_map>
#include <memory>
#include "blocks/internal/block.hpp"
#include "blocks/internal/sprite/block_sprite.hpp"
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

        void AddBlock(std::string id, std::shared_ptr<Block> block);
        void RemoveBlock(std::string id);
        std::weak_ptr<Block> GetHoveredBlock(SDL_FPoint mousePos);

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
        std::unordered_map<std::string, std::shared_ptr<Block>> placedBlocks;
        std::unordered_map<std::string, std::weak_ptr<BlockSprite>> transforms;
        std::vector<std::weak_ptr<Block>> sourceBlocks;
        std::unordered_map<std::shared_ptr<Block>, bool, BlockHash> blockProcessed;
        std::stack<std::shared_ptr<Block>> processStack;
    };
}
    