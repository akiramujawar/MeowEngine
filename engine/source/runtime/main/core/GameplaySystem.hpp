//
// Created by Akira Mujawar on 17/04/26.
//

#ifndef MEOWENGINE_MAINSYSTEM_HPP
#define MEOWENGINE_MAINSYSTEM_HPP

// #include <double_buffer.hpp>
//
// #include <PhysicsSnapshot.hpp>
// #include <RenderSnapshot.hpp>
#include <World.hpp>

namespace MeowEngine::Runtime {
    /**
     * Reads physics snapshot from physics system & applies to World
     * Prepares render & physics snapshot (to be utilised by respective systems)
     * Emits commands if required for physics / render systems
     */
    struct GameplaySystem {
        // DoubleBuffer<RenderSnapshot> RenderSnapshot;
        // DoubleBuffer<PhysicsSnapshot> PhysicsSnapshot;

        World World;

    private:
        void Update();
    };

}


#endif //MEOWENGINE_MAINSYSTEM_HPP