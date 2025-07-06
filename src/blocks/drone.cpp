#include "blocks/emitters/drone.hpp"
#include "systems/noteframe_manager.hpp"

MM::Blocks::Drone::Drone()
{
    m_sprite->SetOverlay(MM::Systems::TexManager::Instance().GetTexture("Drone"));
    input = std::make_shared<MM::BlockPort::PulseIn>(MM::BlockPort::PulseIn{"Input", {-1, 0}, this->shared_from_this()});
    output = std::make_shared<MM::BlockPort::SignalOut>(MM::BlockPort::SignalOut{"Output", {1, 0}, this->shared_from_this()});
}


void MM::Blocks::Drone::Update()
{
    state ^= input->GetState();
    output->SetState(state);
}

void MM::Blocks::Drone::Reset()
{
    input->Reset();
    output->Reset();
}

std::vector<std::weak_ptr<Block>> MM::Blocks::Drone::Propagate()
{
    std::vector<std::weak_ptr<Block>> connectedBlocks;

    output->Send();
    connectedBlocks.push_back(output->GetPort().lock()->GetParent());
}

bool MM::Blocks::Drone::IsReady()
{
    return input->isReady();
}
