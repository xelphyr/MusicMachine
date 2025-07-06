#pragma once
#include <imgui.h>

class UIElement
{
public:
    virtual ~UIElement(){};
    virtual void Update(){};
    virtual void Render(){};
};