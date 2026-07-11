//
// Created by Akira Mujawar on 30/06/26.
//

#ifndef MEOWENGINE_FIXEDTIMING_HPP
#define MEOWENGINE_FIXEDTIMING_HPP

#include <cstdlib>

namespace MeowEngine::Core {
    class FixedTiming {
    public:
        explicit FixedTiming(float fixedDeltaTime = 1/60.0f);

        void Wait();

        [[nodiscard]] float GetFixedDeltaTime() const;

    private:
        float FixedDeltaTime;
        uint64_t Frequency;
        uint64_t NextTick;
    };
}

#endif //MEOWENGINE_FIXEDTIMING_HPP