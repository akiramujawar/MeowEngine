//
// Created by Akira Mujawar on 30/08/24.
//

#ifndef MEOWENGINE_RIGIDBODY_COMPONENT_HPP
#define MEOWENGINE_RIGIDBODY_COMPONENT_HPP

#include <component_base.hpp>
#include <transform3d_component.hpp>
#include "PxPhysicsAPI.h"

using namespace MeowEngine::entity;

namespace MeowEngine::entity {
    class RigidbodyComponent : public MeowEngine::entity::ComponentBase {
    public:
        REFLECT_COMPONENT(RigidbodyComponent)
        static void Reflect();

        explicit RigidbodyComponent();
        virtual ~RigidbodyComponent() = default;

        /**
         * update transform using rigidbody transform
         * SyncTransformAndRigidbody()
         * @param inTransform
         */
        void UpdateTransform(entity::Transform3DComponent& inTransform);

        /**
         * update rigidbody transform using transform
         * SyncRigidbody
         * @param inTransform
         */
        void OverrideTransform(entity::Transform3DComponent& inTransform);

        void AddDelta(Vector3 inDelta, Quaternion pDelta);
        void CacheDelta(Vector3 inDelta, Quaternion pDelta);

        void SetPhysicsBody(physx::PxRigidDynamic* inBody);
        physx::PxRigidDynamic* GetPhysicsBody();

    private:
        physx::PxRigidDynamic* DynamicBody;

        /**
         * When physics is free, we move the cached delta to position delta
         */
        Vector3 PositionDelta;
        Quaternion QuaternionDelta;

        /**
         * Main thread position delta is cached when physics buffer is busy
         * This is accumulated when physics thread is busy.
         * This resets when physics thread is free, and is moved to PositionDelta
         * TODO: Rework on this, to something like physics command.
         * Main thread throws commands to physics
         * Physics creates a snap shot of data to.
         * We will be keep 3 buffers even though it might be heavy on memory
         * This is learning project and not everything has to be perfect! <3
         */
        Vector3 PositionCachedDelta;
        Quaternion QuaternionCachedDelta;
    };
}


#endif //MEOWENGINE_RIGIDBODY_COMPONENT_HPP
