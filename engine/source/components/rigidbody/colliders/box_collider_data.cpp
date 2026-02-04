//
// Created by Akira Mujawar on 30/08/24.
//

#include "box_collider_data.hpp"
#include "entt_reflection_wrapper.hpp"

using namespace MeowEngine::entity;

void BoxColliderData::Reflect() {
    REGISTER_PROPERTY(BoxColliderData, Size, MeowEngine::math::Vector3);

    MeowEngine::Log("Reflected", "BoxColliderData");
}

BoxColliderData::BoxColliderData() {
    Size = MeowEngine::math::Vector3(0.5f, 0.5f, 0.5f);
    Geometry = physx::PxBoxGeometry(physx::PxVec3(0.5f, 0.5f, 0.5f));
}

BoxColliderData::BoxColliderData(MeowEngine::math::Vector3 inSize) {
    Size = inSize;
    Geometry = physx::PxBoxGeometry(physx::PxVec3(inSize.X, inSize.Y, inSize.Z));
}

physx::PxGeometry& BoxColliderData::GetGeometry() {
    return Geometry;
}
