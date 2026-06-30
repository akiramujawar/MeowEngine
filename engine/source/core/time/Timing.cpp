//
// Created by Akira Mujawar on 17/04/26.
//

#include <Timing.hpp>
#include <SDL_API.hpp>
#include <Public/Threading/Include.hpp>

namespace MeowEngine::Core {

    Timing::Timing()
        : MaxFrameRate(1.0f/30)
        , Frequency(SDL_GetPerformanceFrequency())
        , FrameRateUpdateInterval(1)
        , FrameStartTime(SDL_GetPerformanceCounter())
        , FrameTimeAccumulator()
        , FrameRate(1)
        , DeltaTime(0)
    {}

    void Timing::SetMaxFrameRate(const float maxFrameRate) {
        MaxFrameRate = 1.0f / maxFrameRate;
    }

    void Timing::SetFrameRateUpdateInterval(const float updateInterval) {
        FrameRateUpdateInterval = updateInterval;
    }

    // void Timing::SetFixedDeltaTime(const float fixedDeltaTime) {
    //     FixedDeltaTime = fixedDeltaTime;
    // }

    void Timing::Schedule(Threading::Scheduler& scheduler) {
        scheduler.AddTask([this]() {
            Update();
        });
    }

    void Timing::Wait() const {
        Uint64 frameEndTime = SDL_GetPerformanceCounter();
        double frameDuration = (double) (frameEndTime - FrameStartTime) / Frequency;

        while (frameDuration < MaxFrameRate) {
            frameEndTime = SDL_GetPerformanceCounter();
            frameDuration = (double) (frameEndTime - FrameStartTime) / Frequency;
        }

        // previousTime = frameEndTime;
    }

    void Timing::Update() {
        PT_PROFILE_SCOPE;

        PreviousFrameStartTime = FrameStartTime;
        FrameStartTime = SDL_GetPerformanceCounter();

        uint64_t frameTimeDifference = FrameStartTime - PreviousFrameStartTime;
        DeltaTime = static_cast<float>(frameTimeDifference) / Frequency;
        FrameTimeAccumulator += DeltaTime;

        FrameCountPerUpdateInterval++;

        if (FrameTimeAccumulator >= FrameRateUpdateInterval) {
            // FrameRate = FrameCountPerUpdateInterval;
            const auto frameRate = static_cast<float>(FrameCountPerUpdateInterval) / FrameTimeAccumulator;
            FrameRate = static_cast<int>(frameRate);

            FrameTimeAccumulator -= FrameRateUpdateInterval;
            FrameCountPerUpdateInterval = 0;
        }

        // add delta time until 0.25
        // each add =


        // MeowEngine::Log("Delta", std::to_string(FrameRate));
        // double frameDuration = (double)(frameEndTime - FrameStartTime) / Frequency;
        // MeowEngine::Log("FrameDuration", std::to_string(FrameRate));
    }

    float Timing::GetDeltaTime() const {
        return static_cast<float>(DeltaTime);
    }

    // float Timing::GetFixedDeltaTime() const {
    //     return FixedDeltaTime;
    // }

    int Timing::GetFrameRate() const {
        return FrameRate;
    }

}
