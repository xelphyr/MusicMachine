#include "ui/add_element.hpp"
#include "systems/event_bus.hpp"
#include "events/add_block_event.hpp"
#include "blocks/emitters/drone.hpp"
#include "blocks/sources/pulse_source.hpp"

void MM::UI::AddElement::Update()
{
    
}

void MM::UI::AddElement::Render()
{
    ImGui::Begin("Add Element");
    if (ImGui::Button("Add a drone thingy"))
    {
        auto drone = std::make_shared<MM::Blocks::Drone>();
        MM::Systems::EventBus::Instance().Emit<AddBlockEvent>({std::dynamic_pointer_cast<Block>(drone)});
    }
    if (ImGui::Button("Add a pulse thingy"))
    {
        auto pulseSource = std::make_shared<MM::Blocks::PulseSource>();
        MM::Systems::EventBus::Instance().Emit<AddBlockEvent>({std::dynamic_pointer_cast<Block>(pulseSource)});
    }
    ImGui::End();
}
