//
// Created by Akira Mujawar on 30/06/26.
//

#ifndef MEOWENGINE_FIXEDTIMING_HPP
#define MEOWENGINE_FIXEDTIMING_HPP

#include <cstdlib>

namespace MeowEngine::Core {
    class FixedTiming {
    public:
        explicit FixedTiming(float fixedDeltaTime = 1.0f / 250.0f);

        void Wait();

        [[nodiscard]] float GetFixedDeltaTime() const;

    private:
        float m_FixedDeltaTime;
        uint64_t m_Frequency;
        uint64_t m_NextTick;
    };
}

#endif //MEOWENGINE_FIXEDTIMING_HPP