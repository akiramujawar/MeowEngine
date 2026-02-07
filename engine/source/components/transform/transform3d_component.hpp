//
// Created by Akira Mujawar on 03/07/24.
//

#ifndef MEOWENGINE_TRANSFORM3D_COMPONENT_HPP
#define MEOWENGINE_TRANSFORM3D_COMPONENT_HPP

#include "transform_component_base.hpp"
#include "math_wrapper.hpp"

namespace MeowEngine::entity {
    class Transform3DComponent : public MeowEngine::entity::TransformComponentBase {
    public:
        REFLECT(Transform3DComponent)
        static void Reflect();

        Transform3DComponent(const glm::mat4& inProjectionMatrix);
        Transform3DComponent(const glm::mat4& inProjectionMatrix, MeowEngine::math::Vector3, MeowEngine::math::Vector3, MeowEngine::math::Quaternion rotation);
        Transform3DComponent(const glm::mat4& inProjectionMatrix, MeowEngine::math::Vector3, MeowEngine::math::Vector3, MeowEngine::math::Vector3 eulerRotation);
        Transform3DComponent(const glm::mat4& inProjectionMatrix, MeowEngine::math::Vector3, MeowEngine::math::Vector3, glm::vec3 rotationAxis, float rotationDegrees);

        void CalculateTransformMatrix(const glm::mat4& inProjectionMatrix);

        void Update(const float& deltaTime) override;
        void RotateBy(const float& degrees);

        math::Vector3 GetForward();

        MeowEngine::math::Vector3 Position;
        MeowEngine::math::Vector3 Scale;
        MeowEngine::math::Quaternion RotationTest;
        MeowEngine::math::Vector3 RotationTest2;

        // find proper way to handle rotations
        glm::vec3 RotationAxis;
        float RotationDegrees;
        glm::vec4 Rotation;

        glm::mat4 IdentityMatrix;
        glm::mat4 TransformMatrix;

        static math::Vector3 GetFront() {}
        static math::Vector3 GetRight() {}
        static math::Vector3 GetUp() {}

        static math::Matrix4x4 CreateViewMatrix() {
            // 3x3 rotation matrix
            // 4x4 matrix with added rotation and position
        }
    };
}


#endif //MEOWENGINE_TRANSFORM3D_COMPONENT_HPP
