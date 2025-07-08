#include "blocks/sources/pulse_source.hpp"
#include "systems/sprite_manager.hpp"


MM::Blocks::PulseSource::PulseSource()
{
    m_sprite = std::make_shared<BlockSprite>(BlockSprite({0,0}, {5,5},"PulseSource"));
    m_name = "Pulse Source";
    m_id = MM::Helpers::generate_uuid();
    MM::Systems::SpriteManager::Instance().AddSprite(m_id, m_sprite);
    std::cout << "Pulse Source created with ID: " << m_id << "\n";
}

void MM::Blocks::PulseSource::Init()
{
    output = std::make_shared<MM::BlockPort::PulseOut>(MM::BlockPort::PulseOut{"Output", {1, 0}, this->shared_from_this()});
    MM::Systems::SpriteManager::Instance().AddPort(output->GetID(), output);
}

void MM::Blocks::PulseSource::Update() 
{
    output->SetState();
}

void MM::Blocks::PulseSource::Reset()
{
    output->Reset();
}

std::vector<std::weak_ptr<Block>> MM::Blocks::PulseSource::Propagate()
{
    std::vector<std::weak_ptr<Block>> outputBlocks;
    output->Send();
    outputBlocks.push_back(output->GetPort().lock()->GetParent());
    return outputBlocks;
}

bool MM::Blocks::PulseSource::IsReady()
{
    return true;
}
