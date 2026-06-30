//
// Created by Akira Mujawar on 30/06/26.
//

#include "FixedTiming.hpp"

#include <SDL_API.hpp>
#include <thread>

namespace MeowEngine::Core {
    FixedTiming::FixedTiming(float fixedDeltaTime)
        : m_FixedDeltaTime(fixedDeltaTime)
        , m_Frequency(SDL_GetPerformanceFrequency())
        , m_NextTick(SDL_GetPerformanceCounter())
    {}

    void FixedTiming::Wait() {
        m_NextTick += static_cast<uint64_t>(m_FixedDeltaTime * m_Frequency);

        while (SDL_GetPerformanceCounter() < m_NextTick) {
            std::this_thread::yield();
        }
    }

    float FixedTiming::GetFixedDeltaTime() const {
        return m_FixedDeltaTime;
    }
}
