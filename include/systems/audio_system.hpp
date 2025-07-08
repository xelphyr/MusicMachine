#pragma once
#include "audio/audio.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include <mutex>

namespace MM::Systems
{
    class AudioSystem
    {
    public:
        static AudioSystem& Instance()
        {
            static AudioSystem instance;
            return instance;
        }

        AudioSystem(const AudioSystem&) = delete;
        AudioSystem& operator=(const AudioSystem&) = delete;

        void Init();
        void Update();
        void Shutdown();

        void AddAudioSource(std::string id, const Audio& source);
        void RemoveAudioSource(std::string id);

    private:
        AudioSystem(){} ;
        ~AudioSystem() {};

        std::unordered_map<std::string, Audio> audioSources;

        SDL_AudioDeviceID audioDevice;
        SDL_AudioStream* audioStream = nullptr;
        SDL_AudioSpec audioSpec;
        std::mutex audioMutex;

        static void AudioCallback(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount);
    };
}
