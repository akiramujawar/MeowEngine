//
// Created by Akira Mujawar on 03/07/24.
//

#ifndef MEOWENGINE_TRANSFORM3D_COMPONENT_HPP
#define MEOWENGINE_TRANSFORM3D_COMPONENT_HPP

#include "transform_component_base.hpp"
#include "Public/Math.hpp"

namespace MeowEngine::Runtime {
    class Transform3DComponent : public TransformComponentBase {
    public:
        REFLECT_COMPONENT(Transform3DComponent)
        static void Reflect();

        // Transform3DComponent();
        // Transform3DComponent(const glm::mat4& inProjectionMatrix);
        // Transform3DComponent(const glm::mat4& inProjectionMatrix, Vector3, Vector3, Quaternion rotation);
        // Transform3DComponent(const glm::mat4& inProjectionMatrix, Vector3, Vector3, Vector3 eulerRotation);
        // Transform3DComponent(const glm::mat4& inProjectionMatrix, Vector3, Vector3, glm::vec3 rotationAxis, float rotationDegrees);

        void CalculateTransformMatrix(const glm::mat4& inProjectionMatrix);

        void Update(const float& deltaTime) override;

    public:
        Transform Local;
        // Vector3 Position;
        // Vector3 Scale;
        // Quaternion Rotation;
        // Vector3 Euler;
        // Vector3 Up;
        // Vector3 Forward;

        // find proper way to handle rotations
//        glm::vec3 RotationAxis;
//        float RotationDegrees;
//        glm::vec4 Rotation;

        // glm::mat4 IdentityMatrix;
        // glm::mat4 TransformMatrix;
    };
}


#endif //MEOWENGINE_TRANSFORM3D_COMPONENT_HPP
