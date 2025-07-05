#include "systems/block_manager.hpp"

template <typename T>
using SP = std::shared_ptr<T>;
template <typename T>
using WP = std::weak_ptr<T>;

void MM::Systems::BlockManager::RunFrame(const NoteFrameEvent& event)
{
    ResetFrame();
    ProcessFrame();
}


void MM::Systems::BlockManager::ResetFrame() 
{
    for (auto& block : placedBlocks)
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
                processStack.push(block.lock());
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
