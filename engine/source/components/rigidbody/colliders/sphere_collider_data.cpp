//
// Created by Akira Mujawar on 12/02/25.
//

#include "sphere_collider_data.hpp"

#include "entt_reflection_wrapper.hpp"

namespace MeowEngine {
    void SphereColliderData::Reflect() {
        REGISTER_PROPERTY(SphereColliderData, Radius, float);

        MeowEngine::Log("Reflected", "SphereColliderData");
    }

    SphereColliderData::SphereColliderData() {
        Geometry = physx::PxSphereGeometry(0.5f);
    }

    SphereColliderData::SphereColliderData(float inRadius) {
        Radius = inRadius;
        Geometry = physx::PxSphereGeometry(inRadius);
    }

    physx::PxGeometry &SphereColliderData::GetGeometry() {
        return Geometry;
    }

} // MeowEngine