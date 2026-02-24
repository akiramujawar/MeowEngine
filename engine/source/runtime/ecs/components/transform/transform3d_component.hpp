//
// Created by Akira Mujawar on 03/07/24.
//

#ifndef MEOWENGINE_TRANSFORM3D_COMPONENT_HPP
#define MEOWENGINE_TRANSFORM3D_COMPONENT_HPP

#include "transform_component_base.hpp"
#include "Math.hpp"

namespace MeowEngine::entity {
    class Transform3DComponent : public MeowEngine::entity::TransformComponentBase {
    public:
        REFLECT_COMPONENT(Transform3DComponent)
        static void Reflect();

        Transform3DComponent(const glm::mat4& inProjectionMatrix);
        Transform3DComponent(const glm::mat4& inProjectionMatrix, Vector3, Vector3, Quaternion rotation);
        Transform3DComponent(const glm::mat4& inProjectionMatrix, Vector3, Vector3, Vector3 eulerRotation);
        Transform3DComponent(const glm::mat4& inProjectionMatrix, Vector3, Vector3, glm::vec3 rotationAxis, float rotationDegrees);

        void CalculateTransformMatrix(const glm::mat4& inProjectionMatrix);

        void Update(const float& deltaTime) override;
        void RecalculateEuler();

        Vector3 GetForward();
        static Vector3 GetFront() {}
        static Vector3 GetRight() {}
        static Vector3 GetUp() {}

        static Matrix4x4 CreateViewMatrix() {
            // 3x3 rotation matrix
            // 4x4 matrix with added rotation and position
        }

    private:
        void OnRotationReflect();

    public:
        Vector3 Position;
        Vector3 Scale;
        Quaternion Rotation;
        Vector3 Euler;

        // find proper way to handle rotations
//        glm::vec3 RotationAxis;
//        float RotationDegrees;
//        glm::vec4 Rotation;

        glm::mat4 IdentityMatrix;
        glm::mat4 TransformMatrix;
    };
}


#endif //MEOWENGINE_TRANSFORM3D_COMPONENT_HPP
