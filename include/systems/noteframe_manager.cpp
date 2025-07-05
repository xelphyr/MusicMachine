#include "systems/noteframe_manager.hpp"

using Clock = std::chrono::steady_clock;

MM::Systems::NoteframeManager::NoteframeManager()
{
    lastTick = Clock::now();
}

void MM::Systems::NoteframeManager::Update()
{
    auto now = Clock::now();

    float delta = std::chrono::duration<float>(now-lastTick).count();

    lastTick = now;

    accumDelta += delta;

    while (accumDelta>60.f/bpm)
    {
        EventBus::Instance().Emit<NoteFrameEvent>({currFrame++});
        accumDelta = accumDelta-60.f/bpm;
    }
}