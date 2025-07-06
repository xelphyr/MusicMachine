#include "systems/connection_manager.hpp"

void MM::Systems::ConnectionManager::RenderConnections()
{
    SDL_SetRenderDrawColor(RenderContext::Instance().renderer, 255, 255, 255, 255); // Set color to white
    for (const auto& connection : connections)
    {
        if (auto outPort = connection.first.lock())
        {
            if (auto inPort = connection.second.lock())
            {
                SDL_FPoint outPos = outPort->GetPosition();
                SDL_FPoint inPos = inPort->GetPosition();

                // Render a line from outPort to inPort
                SDL_RenderLine(RenderContext::Instance().renderer, 
                                   static_cast<int>(outPos.x), static_cast<int>(outPos.y),
                                   static_cast<int>(inPos.x), static_cast<int>(inPos.y));
            }
        }
    }
}

void MM::Systems::ConnectionManager::AddConnection(std::shared_ptr<PortOut> outPort, std::shared_ptr<PortIn> inPort)
{
    connections.emplace_back(outPort, inPort);
}

void MM::Systems::ConnectionManager::RemoveConnection(std::shared_ptr<Port> outPort, std::shared_ptr<Port> inPort)
{
}

std::weak_ptr<Port> MM::Systems::ConnectionManager::GetConnectedInPort(std::shared_ptr<Port> outPort) const
{
    return std::weak_ptr<Port>();
}
