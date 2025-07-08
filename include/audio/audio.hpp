#pragma once

#include <SDL3/SDL.h>
#include <cmath>

struct Audio {
    float phase = 0.0f;            // Current phase (0.0 - 1.0)
    float frequency = 440.0f;      // Hz
    float duration = 0.5f;         // Total duration (seconds)
    float elapsed = 0.0f;          // Playback progress
    bool expired = false;          // Flag for removal

    float sampleRate = 44100.0f;
    float amplitude = 1.0f;        // Volume
    
    bool loop = false;           // Loop playback
    float falloffTimer{1.f};
    enum class WaveType { Sine, Square, Triangle, Sawtooth } waveType;

    void Generate(float* buffer, int frames) {
        if (expired) return;

        for (int i=0;i<frames;i++) {
            float sample = 0.0f;
            // Advance time
            elapsed += 1.0f / sampleRate;
            if (elapsed >= duration) 
            {
                if (loop) {
                    elapsed = 0.0f;
                    phase = 0.0f;
                } else {
                    expired = true;
                    break;
                }
            }
            switch (waveType) 
            {
                case WaveType::Sine:
                    sample = std::sinf(phase * 2.0f * 3.1415);
                    break;
                case WaveType::Square:
                    sample = (phase < 0.5f) ? 1.0f : -1.0f;
                    break;
                case WaveType::Triangle:
                    sample = 4.0f * fabsf(phase - 0.5f) - 1.0f;
                    break;
                case WaveType::Sawtooth:
                    sample = 2.0f * phase - 1.0f;
                    break;
            }

            sample *= amplitude;

            // Advance phase
            phase += frequency / sampleRate;
            if (phase >= 1.0f) phase -= 1.0f;

            buffer[i*2  ] += sample; // Stereo output
            buffer[i*2+1] += sample; // Stereo output
        }
    }
};

