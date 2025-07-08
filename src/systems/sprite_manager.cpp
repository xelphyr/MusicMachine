#include "systems/sprite_manager.hpp"

#define portSize 2

void MM::Systems::SpriteManager::Update()
{
    
}

void MM::Systems::SpriteManager::Render()
{
    // Render all sprites
    for (const auto& [name, sprite] : sprites)
    {
        if (auto sp = sprite.lock())
        {
            SDL_FPoint pos = MM::Helpers::WorldToScreen(sp->GetPosition());
            SDL_FPoint scale = sp->GetScale();
            scale.x *= Camera::Instance().zoom;
            scale.y *= Camera::Instance().zoom;

            SDL_FRect rect = {
                pos.x - scale.x / 2.f,
                pos.y - scale.y / 2.f,
                scale.x,
                scale.y
            };

            SDL_RenderTexture(RenderContext::Instance().renderer, sp->GetOverlay(), nullptr, &rect);
        }
    }

    // Render all ports
    for (const auto& [name, port] : ports)
    {
        if (auto p = port.lock())
        {
            SDL_RenderPoint(RenderContext::Instance().renderer, 
                MM::Helpers::WorldToScreen(p->GetPosition()).x, 
                MM::Helpers::WorldToScreen(p->GetPosition()).y);
        }
    }
}

//USE WORLDPOS OF MOUSE
std::weak_ptr<BlockSprite> MM::Systems::SpriteManager::GetHoveredSprite(SDL_FPoint mousePos)
{
    for (const auto& [name, sprite] : sprites)
    {
        if (auto sp = sprite.lock())
        {
            SDL_FPoint pos = sp->GetPosition();
            // Assuming GetScale() returns the size of the sprite
            SDL_FPoint scale = sp->GetScale();

            // Check if mouse is within the sprite's bounds
            if (mousePos.x >= pos.x-scale.x/2.f && mousePos.x <= pos.x + scale.x/2.f &&
                mousePos.y >= pos.y-scale.y/2.f && mousePos.y <= pos.y + scale.y/2.f)
            {
                return sprite;
                std::cout << "Hovered sprite at position: " << pos.x << ", " << pos.y << std::endl;
            }
        }
    }
    return std::weak_ptr<BlockSprite>();
}

//USE WORLDPOS OF MOUSE
std::weak_ptr<Port> MM::Systems::SpriteManager::GetHoveredPort(SDL_FPoint mousePos)
{
    for (const auto& [name, port] : ports)
    {
        if (auto p = port.lock())
        {
            SDL_FPoint position = p->GetPosition();
            // Assuming the port is a point, check if mouse is at the port's position
            if (mousePos.x >= position.x - portSize/2.f && mousePos.x <= position.x + portSize/2.f &&
                mousePos.y >= position.y - portSize/2.f && mousePos.y <= position.y + portSize/2.f)
            {
                return port;
            }
        }
    }
    return std::weak_ptr<Port>();
}
