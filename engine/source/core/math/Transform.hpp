//
// Created by Akira Mujawar on 27/06/26.
//

#ifndef MEOWENGINE_TRANSFORM_HPP
#define MEOWENGINE_TRANSFORM_HPP

#include "Object.hpp"
#include "vector3.hpp"
#include "Quaternion.hpp"

namespace MeowEngine::Core::Math {
    class Transform : Types::Object {
        REFLECT_VALUE(Transform)
        static void Reflect();

    public:
        Transform();
        std::string GetClassName() override { return "Transform"; };

        [[nodiscard]] Vector3 GetForward() const;
        [[nodiscard]] Vector3 GetRight() const;
        [[nodiscard]] Vector3 GetUp() const;

        [[nodiscard]] Vector3 GetPosition() const { return Position; };
        [[nodiscard]] Vector3 GetScale() const { return Scale; };
        [[nodiscard]] Vector3 GetEuler() const { return Euler; };
        [[nodiscard]] Quaternion GetQuaternion() const { return Quat; };

        void SetPosition(const Vector3& position);
        void SetScale(const Vector3& scale);
        void SetRotation(const Vector3& euler);
        void SetRotation(const Quaternion& quat);

        void CalculateTransformMatrix(const glm::mat4 &inProjectionMatrix);

    private:
        void OnEulerReflect();

    public:
        static Matrix4x4 ToMatrix();
        static Matrix4x4 LookAtRH(Vector3 position, Vector3 target, Vector3 up);

    private:
        Vector3 Position;
        Vector3 Scale;
        Quaternion Quat;
        Vector3 Euler;

        Matrix4x4 IdentityMatrix {};
        Matrix4x4 TransformMatrix {};
    };
}


#endif //MEOWENGINE_TRANSFORM_HPP