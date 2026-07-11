//
// Created by Akira Mujawar on 30/06/26.
//

#include "FixedTiming.hpp"

#include <SDL_API.hpp>
#include <thread>

namespace MeowEngine::Core {
    FixedTiming::FixedTiming(float fixedDeltaTime)
        : FixedDeltaTime(fixedDeltaTime)
        , Frequency(SDL_GetPerformanceFrequency())
        , NextTick(SDL_GetPerformanceCounter())
    {}

    void FixedTiming::Wait() {
        NextTick += static_cast<uint64_t>(FixedDeltaTime * Frequency);

        while (SDL_GetPerformanceCounter() < NextTick) {
            std::this_thread::yield();
        }
    }

    float FixedTiming::GetFixedDeltaTime() const {
        return FixedDeltaTime;
    }
}
