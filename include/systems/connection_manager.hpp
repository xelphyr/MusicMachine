#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <SDL3/SDL.h>
#include "blocks/internal/ports/port_in.hpp"
#include "blocks/internal/ports/port_out.hpp"
#include "systems/render_context.hpp"

namespace MM::Systems
{
    class ConnectionManager
    {
    public:
        static ConnectionManager& Instance()
        {
            static ConnectionManager instance;
            return instance;
        }

        ConnectionManager(const ConnectionManager&) = delete;
        ConnectionManager& operator=(const ConnectionManager&) = delete;

        void RenderConnections();

        void AddConnection(std::shared_ptr<PortOut> outPort, std::shared_ptr<PortIn> inPort);
        void RemoveConnection(std::shared_ptr<Port> outPort, std::shared_ptr<Port> inPort);
        std::weak_ptr<Port> GetConnectedInPort(std::shared_ptr<Port> outPort) const;

    private:
        ConnectionManager() = default;
        ~ConnectionManager() = default;

        std::vector<std::pair<std::weak_ptr<PortOut>, std::weak_ptr<PortIn>>> connections;
    };
} // namespace MM::Systems