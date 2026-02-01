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
        static void Reflect();

        Transform3DComponent(const glm::mat4& inProjectionMatrix);
        Transform3DComponent(const glm::mat4& inProjectionMatrix, MeowEngine::math::Vector3, MeowEngine::math::Vector3, MeowEngine::math::Quaternion rotation);
        Transform3DComponent(const glm::mat4& inProjectionMatrix, MeowEngine::math::Vector3, MeowEngine::math::Vector3, MeowEngine::math::Vector3 eulerRotation);
        Transform3DComponent(const glm::mat4& inProjectionMatrix, MeowEngine::math::Vector3, MeowEngine::math::Vector3, glm::vec3 rotationAxis, float rotationDegrees);

        void CalculateTransformMatrix(const glm::mat4& inProjectionMatrix);

        void Update(const float& deltaTime) override;
        void RotateBy(const float& degrees);

        MeowEngine::math::Vector3 Position;
        glm::vec3 Scale;

        // find proper way to handle rotations
        glm::vec3 RotationAxis;
        float RotationDegrees;
        glm::vec4 Rotation;

        glm::mat4 IdentityMatrix;
        glm::mat4 TransformMatrix;
    };
}


#endif //MEOWENGINE_TRANSFORM3D_COMPONENT_HPP
