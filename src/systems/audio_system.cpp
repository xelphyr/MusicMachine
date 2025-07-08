#include "systems/audio_system.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace MM::Systems;

void AudioSystem::Init()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        SDL_Log("Failed to init SDL Audio: %s", SDL_GetError());
        return;
    }

    audioSpec.freq = 44100;
    audioSpec.format = SDL_AUDIO_F32;
    audioSpec.channels = 2;

    audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec);
    audioStream = SDL_OpenAudioDeviceStream(audioDevice, &audioSpec, AudioCallback, &audioSources);
}

void AudioSystem::Shutdown()
{
    SDL_CloseAudioDevice(audioDevice);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    std::cout << "Audio system shut down.\n";
}

void AudioSystem::Update()
{
    
}

void AudioSystem::AddAudioSource(std::string id, const Audio& source)
{
    std::scoped_lock lock(audioMutex);
    audioSources[id] = source;
}

void AudioSystem::RemoveAudioSource(std::string id)
{
    std::scoped_lock lock(audioMutex);
    if (audioSources.find(id) != audioSources.end())
    {
        audioSources.erase(id);
    }
    else
    {
        std::cout << "Audio source with ID " << id << " not found or already expired.\n";
    }
}


void AudioSystem::AudioCallback(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount) {
    constexpr int channels = 2;
    constexpr int bytesPerSample = sizeof(float);
    int framesRequested = additional_amount / (bytesPerSample * channels);

    auto* audioSources = static_cast<std::unordered_map<std::string, Audio>*>(userdata);

    std::vector<float> mixBuffer(framesRequested * channels, 0.0f);

    // Mix active sounds into the buffer
    for (auto it = audioSources->begin(); it != audioSources->end(); ) {
        auto& src = it->second;
        if (src.expired) {++
            it = audioSources->erase(it);
        } else {
            src.Generate(mixBuffer.data(), framesRequested);
            ++it;
        }
    }

    // Push to the stream
    SDL_PutAudioStreamData(stream, mixBuffer.data(), additional_amount);
}
