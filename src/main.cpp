#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <iostream>

#include "managers.hpp"

#include "blocks.hpp"
#include "ui.hpp"

#include "camera.hpp"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    std::cout << "Music Machine Renderer Clear Example\n";
    /* Window Setup */
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    std::cout << "Didnt fail\n";

    Camera::Instance().dimensions = {640, 480};

    if (!SDL_CreateWindowAndRenderer("Music Machine", Camera::Instance().dimensions.x, Camera::Instance().dimensions.y, 0, &MM::Systems::RenderContext::Instance().window, &MM::Systems::RenderContext::Instance().renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetWindowResizable(MM::Systems::RenderContext::Instance().window, true);

    /* ImGUI Setup */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(MM::Systems::RenderContext::Instance().window, MM::Systems::RenderContext::Instance().renderer);
    ImGui_ImplSDLRenderer3_Init(MM::Systems::RenderContext::Instance().renderer);


    Camera::Instance().position = {0,0};
    Camera::Instance().zoom = 1; 

    MM::Systems::TexManager::Instance();  // Initialize texture manager
    MM::Systems::SpriteManager::Instance();  // Initialize sprite manager
    MM::Systems::BlockManager::Instance();  // Initialize block manager
    MM::Systems::EventBus::Instance();  // Initialize event bus
    MM::Systems::ConnectionManager::Instance();  // Initialize connection manager

    MM::Systems::UIManager::Instance();  // Initialize UI manager
    MM::Systems::UIManager::Instance().RegisterUI(std::make_shared<MM::UI::AddElement>());
    MM::Systems::UIManager::Instance().RegisterUI(std::make_shared<MM::UI::PortLink>());


    return SDL_APP_CONTINUE; 
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    ImGui_ImplSDL3_ProcessEvent(event);
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_SetRenderDrawColor(MM::Systems::RenderContext::Instance().renderer, 30, 30, 30, 255);
    SDL_RenderClear(MM::Systems::RenderContext::Instance().renderer);

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    Camera::Instance().CheckChanges();

    SDL_SetRenderDrawColor(MM::Systems::RenderContext::Instance().renderer, 255, 255, 255, 255);
    SDL_FRect box = {(2.f-Camera::Instance().position.x+320.f/Camera::Instance().zoom)*Camera::Instance().zoom, (2.f-Camera::Instance().position.y+240.f/Camera::Instance().zoom)*Camera::Instance().zoom, Camera::Instance().zoom*20, Camera::Instance().zoom*20};

    SDL_RenderFillRect(MM::Systems::RenderContext::Instance().renderer, &box);

    MM::Systems::UIManager::Instance().Update();

    MM::Systems::SpriteManager::Instance().Update();
    MM::Systems::SpriteManager::Instance().Render();

    MM::Systems::ConnectionManager::Instance().RenderConnections();

    MM::Systems::NoteframeManager::Instance().Update();

    MM::Systems::UIManager::Instance().Render();
    
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), MM::Systems::RenderContext::Instance().renderer);

    SDL_RenderPresent(MM::Systems::RenderContext::Instance().renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}