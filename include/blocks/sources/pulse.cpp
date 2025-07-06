#include "pulse.hpp"

MM::Blocks::Pulse::Pulse()
{
}

void MM::Blocks::Pulse::Update()
{
    output->SetState();
}

void MM::Blocks::Pulse::Reset()
{
    output->Reset();
}

std::vector<std::weak_ptr<Block>> MM::Blocks::Pulse::Propagate()
{
    std::vector<std::weak_ptr<Block>> outputBlocks;
    output->Send();
    outputBlocks.push_back(output->GetPort().lock()->GetParent());
    return outputBlocks;
}

bool MM::Blocks::Pulse::IsReady()
{
    return true;
}
