#include "ui/add_element.hpp"
#include "systems/event_bus.hpp"
#include "events/add_block_event.hpp"
#include "blocks/emitters/drone.hpp"

void MM::UI::AddElement::Update()
{
    
}

void MM::UI::AddElement::Render()
{
    ImGui::Begin("Add Element");
    if (ImGui::Button("Add a drone thingy"))
    {
        MM::Blocks::Drone drone;
        EventBus::Instance().Emit<AddBlockEvent>({std::make_shared<Block>(drone)});
    }
    ImGui::End();
}
