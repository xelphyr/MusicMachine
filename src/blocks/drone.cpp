#include "blocks/emitters/drone.hpp"
#include "systems/noteframe_manager.hpp"
#include "systems/sprite_manager.hpp"
#include "helpers/gen_uuid.hpp"
#include <string>
#include <iostream>

MM::Blocks::Drone::Drone()
{
    m_sprite = std::make_shared<BlockSprite>(BlockSprite({0,0}, {5,5},"Drone"));
    m_name = "Drone";
    m_id = MM::Helpers::generate_uuid();
    MM::Systems::SpriteManager::Instance().AddSprite(m_id, m_sprite);
    std::cout << "Drone created with ID: " << m_id << std::endl;
}

void MM::Blocks::Drone::Init()
{
    input = std::make_shared<MM::BlockPort::PulseIn>(MM::BlockPort::PulseIn{"Input", {-1, 0}, this->shared_from_this()});
    output = std::make_shared<MM::BlockPort::SignalOut>(MM::BlockPort::SignalOut{"Output", {1, 0}, this->shared_from_this()});
    MM::Systems::SpriteManager::Instance().AddPort(input->GetID(), input);
    MM::Systems::SpriteManager::Instance().AddPort(output->GetID(), output);
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
    if (output->GetPort().lock())
    {
        connectedBlocks.push_back(output->GetPort().lock()->GetParent());
    }
    return connectedBlocks;
}

bool MM::Blocks::Drone::IsReady()
{
    return input->isReady();
}
