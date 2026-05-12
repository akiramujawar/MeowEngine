//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_TIMING_HPP
#define MEOWENGINE_TIMING_HPP

#include <cstdint>

namespace MeowEngine::Core {
    class Timing {
    public:
        Timing();

        void SetMaxFrameRate(float maxFrameRate);
        void SetFrameRateUpdateInterval(float updateInterval);
        void SetFixedDeltaTime(float fixedDeltaTime);

        void Update();

        [[nodiscard]] float GetDeltaTime() const;
        [[nodiscard]] float GetFixedDeltaTime() const;
        [[nodiscard]] int GetFrameRate() const;

        int GetPhysicsSteps();

    private:
        /**
         * Cap the maximum frame rate per second
         */
        float MaxFrameRate;

        /**
         * update frame rate every 'x' seconds
         */
        float FrameRateUpdateInterval;

        /**
         *
         */
        int FrameCountPerUpdateInterval;

        /**
         * Time when new frame start
         */
        uint64_t FrameStartTime;

        /**
         * Previous Time when frame started
         */
        uint64_t PreviousFrameStartTime;

        /**
         * Collects frame time overtime
         */
        float FrameTimeAccumulator;

        int FrameRate;
        uint64_t DeltaTime;
        float FixedDeltaTime;
    };
}


#endif //MEOWENGINE_TIMING_HPP