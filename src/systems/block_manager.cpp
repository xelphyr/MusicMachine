#include "systems/block_manager.hpp"

template <typename T>
using SP = std::shared_ptr<T>;
template <typename T>
using WP = std::weak_ptr<T>;

void MM::Systems::BlockManager::AddBlock(const AddBlockEvent& event)
{
    placedBlocks[event.block->GetID()] = event.block;
    event.block->Init();
    if (event.block->GetType() == Block::Type::Source)
    {
        sourceBlocks.push_back(event.block);
    }
}

void MM::Systems::BlockManager::RemoveBlock(const RemoveBlockEvent& event)
{
    if (placedBlocks.find(event.id) == placedBlocks.end())
    {
        return; // Block not found
    }
    if (placedBlocks[event.id]->GetType() == Block::Type::Source)
    {
        for (auto it = sourceBlocks.begin(); it != sourceBlocks.end();)
        {
            if (it->lock()->GetID() == event.id)
            {
                it = sourceBlocks.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    placedBlocks.erase(event.id);
}

void MM::Systems::BlockManager::RunFrame(const NoteFrameEvent &event)
{
    ResetFrame();
    ProcessFrame();
}

void MM::Systems::BlockManager::ResetFrame() 
{
    for (auto& [name, block] : placedBlocks)
    {
        block->Reset();
    }
}

void MM::Systems::BlockManager::ProcessFrame()
{
    processStack = {};
    blockProcessed.clear();

    //Setup
    for (int i = 0; i<sourceBlocks.size(); i++)
    {
        if (auto sp = sourceBlocks[i].lock())
            processStack.push(sp);
    }

    //Main
    while(processStack.size() != 0)
    {
        SP<Block> currentBlock = processStack.top();
        processStack.pop();

        if (currentBlock->IsReady())
        {
            currentBlock->Update();
            std::vector<WP<Block>> newBlocks = currentBlock->Propagate();
            for (const auto& block : newBlocks)
            {
                if (auto sp = block.lock())
                {
                    processStack.push(sp);
                }
            }
            blockProcessed[currentBlock] = true;
        }
        else 
        {
            blockProcessed[currentBlock] = false;
        }
    }

    //Cleanup
    for (const auto& [block, processed] : blockProcessed )
    {
        if (!processed)
        {
            
        }
    }
}
