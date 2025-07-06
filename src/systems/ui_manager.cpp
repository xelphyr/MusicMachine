#include "systems/ui_manager.hpp"

void MM::Systems::UIManager::Update()
{
    for (auto& ui : uis)
    {
        ui->Update();
    }
}

void MM::Systems::UIManager::Render()
{
    for (auto& ui : uis)
    {
        ui->Render();
    }
}