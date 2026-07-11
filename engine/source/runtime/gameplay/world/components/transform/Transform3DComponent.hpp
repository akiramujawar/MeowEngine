//
// Created by Akira Mujawar on 03/07/24.
//

#ifndef MEOWENGINE_TRANSFORM3D_COMPONENT_HPP
#define MEOWENGINE_TRANSFORM3D_COMPONENT_HPP

#include "IComponent.hpp"
#include "Public/Math.hpp"
#include "TransformAuthorityState.hpp"

namespace MeowEngine::Runtime {
    class Transform3DComponent : public IComponent {
    public:
        REFLECT_COMPONENT(Transform3DComponent)
        static void Reflect();

        [[nodiscard]] Vector3 GetForward() const { return Local.GetForward(); }
        [[nodiscard]] Vector3 GetRight() const { return Local.GetRight(); }
        [[nodiscard]] Vector3 GetUp() const { return Local.GetUp(); }

        [[nodiscard]] Vector3 GetPosition() const { return Local.GetPosition(); };
        [[nodiscard]] Vector3 GetScale() const { return Local.GetScale(); };
        [[nodiscard]] Vector3 GetEuler() const { return Local.GetEuler(); };
        [[nodiscard]] Quaternion GetQuaternion() const { return Local.GetQuaternion(); };
        [[nodiscard]] Matrix4x4 ToMatrix() const { return Local.ToMatrix(); };

        void SetPosition(const Vector3& position);
        void SetScale(const Vector3& scale);
        void SetRotation(const Vector3& euler);
        void SetRotation(const Quaternion& quat);

        /**
         * Do not access directly (internal api)
         * @return
         */
        Transform& GetRootTransform() { return Local; };

    protected:
        Transform Local;
        TransformAuthorityState State = TransformAuthorityState::LOCAL;
    };
}


#endif //MEOWENGINE_TRANSFORM3D_COMPONENT_HPP
