#include "ui/port_link.hpp"
#include "blocks/internal/ports/port.hpp"
#include "blocks/internal/ports/port_in.hpp"
#include "blocks/internal/ports/port_out.hpp"
#include "blocks/internal/ports/signal_in.hpp"
#include "blocks/internal/ports/signal_out.hpp"
#include "blocks/internal/ports/scalar_in.hpp"
#include "blocks/internal/ports/scalar_out.hpp"
#include "blocks/internal/ports/pulse_in.hpp"
#include "blocks/internal/ports/pulse_out.hpp"
#include "systems/sprite_manager.hpp"
#include "systems/connection_manager.hpp"
#include "helpers/screen_world_convert.hpp"

void MM::UI::PortLink::Update()
{
    static std::weak_ptr<Port> selectedPortOut;
    static std::weak_ptr<BlockSprite> selectedBlockSprite;
    ImGuiIO& io = ImGui::GetIO();

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        SDL_FPoint mousePos = { io.MousePos.x, io.MousePos.y };
        mousePos = MM::Helpers::ScreenToWorld(mousePos);
        if (auto port = MM::Systems::SpriteManager::Instance().GetHoveredPort(mousePos).lock())
        {
            if (auto portOut = selectedPortOut.lock())
            {
                if (port->GetType() == Port::SignalOut || port->GetType() == Port::PulseOut || port->GetType() == Port::ScalarOut)
                {
                    // If the port is already selected, deselect it
                    if (selectedPortOut.lock() == port)
                    {
                        selectedPortOut = std::weak_ptr<Port>();
                    }
                    else
                    {
                        // Select the new port
                        selectedPortOut = port;
                    }
                }
                //TODO: Move to ConnectionManager
                else if (port->GetType() == Port::SignalIn && portOut->GetType() == Port::SignalOut)
                {
                    std::dynamic_pointer_cast<MM::BlockPort::SignalIn>(port)->SetPort(std::dynamic_pointer_cast<MM::BlockPort::SignalOut>(portOut));
                    std::dynamic_pointer_cast<MM::BlockPort::SignalOut>(portOut)->SetPort(std::dynamic_pointer_cast<MM::BlockPort::SignalIn>(port));
                    MM::Systems::ConnectionManager::Instance().AddConnection(std::dynamic_pointer_cast<PortOut>(portOut), std::dynamic_pointer_cast<PortIn>(port));
                }
                else if (port->GetType() == Port::ScalarIn && portOut->GetType() == Port::ScalarOut)
                {
                    std::dynamic_pointer_cast<MM::BlockPort::ScalarIn>(port)->SetPort(std::dynamic_pointer_cast<MM::BlockPort::ScalarOut>(portOut));
                    std::dynamic_pointer_cast<MM::BlockPort::ScalarOut>(portOut)->SetPort(std::dynamic_pointer_cast<MM::BlockPort::ScalarIn>(port));
                    MM::Systems::ConnectionManager::Instance().AddConnection(std::dynamic_pointer_cast<PortOut>(portOut), std::dynamic_pointer_cast<PortIn>(port));
                }
                else if (port->GetType() == Port::PulseIn && portOut->GetType() == Port::PulseOut)
                {
                    std::dynamic_pointer_cast<MM::BlockPort::PulseIn>(port)->SetPort(std::dynamic_pointer_cast<MM::BlockPort::PulseOut>(portOut));
                    std::dynamic_pointer_cast<MM::BlockPort::PulseOut>(portOut)->SetPort(std::dynamic_pointer_cast<MM::BlockPort::PulseIn>(port));
                    MM::Systems::ConnectionManager::Instance().AddConnection(std::dynamic_pointer_cast<PortOut>(portOut), std::dynamic_pointer_cast<PortIn>(port));
                }
                else
                {
                    // If the port is not compatible, do nothing or show an error
                    ImGui::Text("Incompatible port types.");
                }
            }
            else
            {
                // If no port is selected, select the clicked port
                selectedPortOut = port;
            }
        }
        else if (auto block = MM::Systems::SpriteManager::Instance().GetHoveredSprite(mousePos).lock())
        {
            // If a block is clicked, select it
            selectedBlockSprite = block;
            selectedPortOut = std::weak_ptr<Port>();
        }
        else
        {
            // If nothing is clicked, deselect everything
            selectedPortOut = std::weak_ptr<Port>();
            selectedBlockSprite = std::weak_ptr<BlockSprite>();
        }
    }

    if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
    {
        // Handle mouse click logic here
        // For example, you might want to start a new port link or select a port.
        selectedBlockSprite = std::weak_ptr<BlockSprite>();
    }

    if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
    {
        if (io.MouseSource == ImGuiMouseSource_Mouse)
        {
            SDL_FPoint mousePos = { io.MousePos.x, io.MousePos.y };
            if (mousePos.x != -FLT_MIN && mousePos.y != -FLT_MIN)
            {
                if (auto blockSprite = selectedBlockSprite.lock())
                {
                    // If a block sprite is selected, update its position
                    blockSprite->SetPosition(MM::Helpers::ScreenToWorld(mousePos));
                }
            }
        }
    }
}

void MM::UI::PortLink::Render()
{

}
