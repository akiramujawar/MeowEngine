//
// Created by Akira Mujawar on 30/08/24.
//

#include "rigidbody_component.hpp"
#include "log.hpp"

void MeowEngine::entity::RigidbodyComponent::Reflect(){
    REGISTER_POINTER(RigidbodyComponent, DynamicBody, physx::PxRigidDynamic*, false, false)
}

MeowEngine::entity::RigidbodyComponent::RigidbodyComponent()
: QuaternionCachedDelta(math::Quaternion::Identity())
, QuaternionDelta(math::Quaternion::Identity()) {

}

void MeowEngine::entity::RigidbodyComponent::SetPhysicsBody(physx::PxRigidDynamic *inBody) {
    DynamicBody = inBody;
}

physx::PxRigidDynamic* MeowEngine::entity::RigidbodyComponent::GetPhysicsBody() {
    return DynamicBody;
}

void RigidbodyComponent::UpdateTransform(Transform3DComponent &inTransform) {
    physx::PxTransform pose = DynamicBody->getGlobalPose();

    // update Position & Quaternion from accumulated delta & physics simulation
    inTransform.Position = math::Vector3{
        pose.p.x + PositionDelta.X,
        pose.p.y + PositionDelta.Y,
        pose.p.z + PositionDelta.Z
    };

    inTransform.Quaternion = math::Quaternion(
        pose.q.w,
        pose.q.x,
        pose.q.y,
        pose.q.z
    );

    inTransform.Quaternion = math::Quaternion::Multiply(inTransform.Quaternion, QuaternionDelta);
    inTransform.RecalculateEuler();
//    math::Quaternion quat = math::Quaternion::Multiply(inTransform.Quaternion, math::Quaternion::Identity());
//    math::Vector3 vec = math::Quaternion::Euler(quat);
//    MeowEngine::Log("Vec" , vec.ToString());

    // 0,0,0 : 90,0,0 : 0,90,0 : 0,0,90 : 45,30,60
//    math::Quaternion quat = math::Quaternion(0,90,0);
//    math::Vector3 vec = math::Quaternion::Euler(quat);
//    MeowEngine::Log("Quat" , quat.ToString());
//    MeowEngine::Log("Vec" , vec.ToString());

    // reset the delta
    PositionDelta = math::Vector3::Zero();
    QuaternionDelta = math::Quaternion::Identity();

    // reapply the final position & quaternion to the physx actor
    pose.p = physx::PxVec3T<float>(
        inTransform.Position.X,
        inTransform.Position.Y,
        inTransform.Position.Z
    );

    pose.q = physx::PxQuatT<float>(
        inTransform.Quaternion.X,
        inTransform.Quaternion.Y,
        inTransform.Quaternion.Z,
        inTransform.Quaternion.W
    );

    DynamicBody->setGlobalPose(pose);
}

void RigidbodyComponent::OverrideTransform(Transform3DComponent &inTransform) {
    physx::PxTransform pose = DynamicBody->getGlobalPose();

    // reapply the final position & quaternion to the physx actor
    pose.p = physx::PxVec3T<float>(
            inTransform.Position.X,
            inTransform.Position.Y,
            inTransform.Position.Z
    );

    pose.q = physx::PxQuatT<float>(
            inTransform.Quaternion.X,
            inTransform.Quaternion.Y,
            inTransform.Quaternion.Z,
            inTransform.Quaternion.W
    );

    DynamicBody->setGlobalPose(pose);
}

void MeowEngine::entity::RigidbodyComponent::CacheDelta(MeowEngine::math::Vector3 inDelta, MeowEngine::math::Quaternion pDelta) {
    PositionCachedDelta += inDelta;
    QuaternionCachedDelta = math::Quaternion::Multiply(QuaternionCachedDelta, pDelta);
}

void MeowEngine::entity::RigidbodyComponent::AddDelta(MeowEngine::math::Vector3 inDelta, MeowEngine::math::Quaternion pDelta) {
    PositionDelta += inDelta + PositionCachedDelta;
    QuaternionDelta = math::Quaternion::Multiply(QuaternionDelta, pDelta);
    QuaternionDelta = math::Quaternion::Multiply(QuaternionDelta, QuaternionCachedDelta);

    PositionCachedDelta = math::Vector3::Zero();
    QuaternionCachedDelta = math::Quaternion::Identity();
}

