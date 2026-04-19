//
// Created by Akira Mujawar on 18/04/26.
//

#ifndef MEOWENGINE_PHYSICSWORLD_HPP
#define MEOWENGINE_PHYSICSWORLD_HPP

#include <unordered_map>
#include <Rigidbody.hpp>

namespace MeowEngine::Runtime {
    struct PhysicsWorld {
        std::unordered_map<uint32_t, Rigidbody> RigidBodies;

    private:
        void SyncData();
        void CreateRigidbody(uint32_t guid);
        void RemoveRigidbody(uint32_t guid);
    };
}

#endif //MEOWENGINE_PHYSICSWORLD_HPP