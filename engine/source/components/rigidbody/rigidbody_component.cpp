//
// Created by Akira Mujawar on 30/08/24.
//

#include "rigidbody_component.hpp"
#include "log.hpp"

void MeowEngine::entity::RigidbodyComponent::Reflect(){
    REGISTER_POINTER(RigidbodyComponent, DynamicBody, physx::PxRigidDynamic*, false)
}

MeowEngine::entity::RigidbodyComponent::RigidbodyComponent() {

}

void MeowEngine::entity::RigidbodyComponent::SetPhysicsBody(physx::PxRigidDynamic *inBody) {
    DynamicBody = inBody;
}

physx::PxRigidDynamic* MeowEngine::entity::RigidbodyComponent::GetPhysicsBody() {
    return DynamicBody;
}

void RigidbodyComponent::UpdateTransform(Transform3DComponent &inTransform) {
    auto pose = DynamicBody->getGlobalPose();
    inTransform.Position.X = pose.p.x + PositionDelta.X;
    inTransform.Position.Y = pose.p.y + PositionDelta.Y;
    inTransform.Position.Z = pose.p.z + PositionDelta.Z;

    PositionDelta.X = 0;
    PositionDelta.Y = 0;
    PositionDelta.Z = 0;

    DynamicBody->setGlobalPose(physx::PxTransform(inTransform.Position.X,inTransform.Position.Y,inTransform.Position.Z));
}

void RigidbodyComponent::OverrideTransform(Transform3DComponent &inTransform) {
    DynamicBody->setGlobalPose(physx::PxTransform(inTransform.Position.X,inTransform.Position.Y,inTransform.Position.Z));
}

void MeowEngine::entity::RigidbodyComponent::CacheDelta(MeowEngine::math::Vector3 inDelta) {
    PositionCachedDelta.X += inDelta.X;
    PositionCachedDelta.Y += inDelta.Y;
    PositionCachedDelta.Z += inDelta.Z;
}

void MeowEngine::entity::RigidbodyComponent::AddDelta(MeowEngine::math::Vector3 inDelta) {
    PositionDelta.X += inDelta.X + PositionCachedDelta.X;
    PositionDelta.Y += inDelta.Y + PositionCachedDelta.Y;
    PositionDelta.Z += inDelta.Z + PositionCachedDelta.Z;

    PositionCachedDelta.X = 0;
    PositionCachedDelta.Y = 0;
    PositionCachedDelta.Z = 0;

//    MeowEngine::Log("Main Thread Delta Sync Write", TestDelta);
}

