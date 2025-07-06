#pragma once

#include "systems/event_bus.hpp"
#include "events/noteframe_event.hpp"

#include <chrono>

namespace MM::Systems
{
    class NoteframeManager
    {
    public:
        static NoteframeManager& Instance()
        {
            static NoteframeManager nfm;
            return nfm;
        }
        NoteframeManager(const NoteframeManager&) = delete;
        NoteframeManager& operator = (const NoteframeManager&) = delete;

        void Update();
        unsigned int GetCurrentFrame() const { return currFrame; }
    private:
        NoteframeManager();
        ~NoteframeManager() {};
        int bpm;
        unsigned int currFrame = 0;
        float accumDelta;
        std::chrono::time_point<std::chrono::steady_clock> lastTick;
    };
}