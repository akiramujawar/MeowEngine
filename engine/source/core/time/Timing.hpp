//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_TIMING_HPP
#define MEOWENGINE_TIMING_HPP

namespace MeowEngine::Core {
    class Timing {
    public:
        Timing();

        void Update();

        float GetDeltaTime();
        float GetFixedDeltaTime();
        double GetFrameRate();

        int GetPhysicsSteps();

    private:
        float Accumulator;
    };
}


#endif //MEOWENGINE_TIMING_HPP