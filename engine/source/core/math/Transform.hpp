//
// Created by Akira Mujawar on 27/06/26.
//

#ifndef MEOWENGINE_TRANSFORM_HPP
#define MEOWENGINE_TRANSFORM_HPP

#include "Public/Core/Include.hpp"
#include "Object.hpp"
#include "vector3.hpp"
#include "quaternion.hpp"

namespace MeowEngine::Core::Math {
    class Transform : Object {
        REFLECT_VALUE(Transform)
        static void Reflect();

    public:
        Transform();
        std::string GetClassName() override { return "Transform"; };

        [[nodiscard]] Vector3 GetEuler() const { return Euler; };
        Vector3 GetForward();

        void SetEuler(const Vector3& euler);
        void SetQuaternion(const Quaternion& quat);

        void CalculateTransformMatrix(const glm::mat4 &inProjectionMatrix);

    private:
        void OnEulerReflect();

    public:
        static Matrix4x4 CreateViewMatrix() {
            // 3x3 rotation matrix
            // 4x4 matrix with added rotation and position
        }

        static Vector3 GetFront() {}
        static Vector3 GetRight() {}
        static Vector3 GetUp() {}

    public:
        Vector3 Position;
        Vector3 Scale;
        Quaternion Quat;
        Vector3 Euler;

        Vector3 Up;
        Vector3 Forward;

        Matrix4x4 IdentityMatrix{};
        Matrix4x4 TransformMatrix{};
    };
}


#endif //MEOWENGINE_TRANSFORM_HPP