#pragma once
#include <vector>
#include <memory>
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

        void Update();
        void Render();

    private:
        UIManager(){};
        ~UIManager(){};
        std::vector<std::shared_ptr<UIElement>> uis;
    };
}