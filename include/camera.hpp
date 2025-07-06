#pragma once
#include <SDL3/SDL.h>
#include <imgui.h>

#include "helpers/vec_convert.hpp"
#include "helpers/sdl_ops.hpp"

#include <iostream>
#include <algorithm>

struct Camera
{
public:
    static Camera& Instance()
    {
        static Camera c;
        return c;
    }

    void CheckChanges()
    {
        using namespace MM::Helpers;
        if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
        {
            ImVec2 delta = ImGui::GetIO().MouseDelta;
            position -= ToSDL_FPoint(delta)/zoom;
        }

        float wheel = ImGui::GetIO().MouseWheel;
        if (wheel != 0.f)
        {
            zoom = std::clamp(zoom+wheel, 0.1f, 10.0f);
            
        }
    }

    Camera(const Camera&) = delete;
    Camera& operator = (const Camera&) = delete;

    SDL_FPoint position;
    SDL_FPoint dimensions;
    float zoom;

private:
    Camera() {}
    ~Camera() {}
};