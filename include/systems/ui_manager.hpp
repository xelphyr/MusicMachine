#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "ui/ui_element.hpp"

namespace MM::Systems
{
    class UIManager
    {   
    public:
        static UIManager& Instance()
        {
            static UIManager uim;
            return uim;
        }
        UIManager(const UIManager&) = delete;
        UIManager& operator = (const UIManager&) = delete;

        void RegisterUI(std::shared_ptr<UIElement> ui)
        {
            uis.push_back(ui);
        }
        void UnregisterUI(std::shared_ptr<UIElement> ui)
        {
            uis.erase(std::remove(uis.begin(), uis.end(), ui), uis.end());
        }

        void Update();
        void Render();

    private:
        UIManager(){};
        ~UIManager(){};
        std::vector<std::shared_ptr<UIElement>> uis;
    };
}