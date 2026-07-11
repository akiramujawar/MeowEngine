//
// Created by Akira Mujawar on 05/07/26.
//

#ifndef MEOWENGINE_PHYSICSWORLDEXTRACTOR_HPP
#define MEOWENGINE_PHYSICSWORLDEXTRACTOR_HPP


#include "EntityHandle.hpp"
#include "PhysicsWorldData.hpp"

namespace MeowEngine::Asset {
    class World;
}

namespace MeowEngine::Runtime {
    class PhysicsWorldExtractor {
    public:
        static void Extract(Asset::World& world, Physics::PhysicsWorldData& data);

    private:
        static void FindColliders(
            Asset::World& world ,
            Physics::PhysicsWorldData& data,
            EntityHandle child,
            Physics::Rigidbody& body
        );
        static std::tuple<bool, Physics::Collider, Physics::PhysicsMaterial> GetColliderData(
            Asset::World& world ,
            EntityHandle handle
        );

    };
}


#endif //MEOWENGINE_PHYSICSWORLDEXTRACTOR_HPP