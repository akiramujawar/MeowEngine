//
// Created by Akira Mujawar on 27/06/26.
//

#include "Transform.hpp"

namespace MeowEngine::Core::Math {
    void Transform::Reflect() {
        REGISTER_PROPERTY(Transform, Position, Vector3, true, true);
        REGISTER_PROPERTY(Transform, Scale, Vector3, true, true);
        REGISTER_PROPERTY(Transform, Quat, Quaternion, false, true);
        REGISTER_PROPERTY_CALLBACK(Transform, Euler, Vector3, true, true, OnEulerReflect);
    }

    Transform::Transform() {}

    Vector3 Transform::GetForward() const {
        return Quat.RotateAroundAxis(Vector3::Forward());
    }

    Vector3 Transform::GetRight() const {
        return Quat.RotateAroundAxis(Vector3::Right());
    }

    Vector3 Transform::GetUp() const {
        return Quat.RotateAroundAxis(Vector3::Up());
    }

    void Transform::SetPosition(const Vector3& position) {
        Position = position;
    }

    void Transform::SetScale(const Vector3& scale) {
        Scale = scale;
    }

    void Transform::SetRotation(const Vector3& euler) {
        Euler = euler;
        Quat = Quaternion(euler);
    }

    void Transform::SetRotation(const Quaternion& quat) {
        Quat = quat;
        Euler = Quaternion::Euler(quat);
    }

    void Transform::CalculateTransformMatrix(const glm::mat4& inProjectionMatrix) {
        Matrix4x4 rotationMatrix = Quat.GetRotationMatrix4x4();

        auto test = Matrix4x4::Identity();

        glm::mat4 identityMatrix =  Matrix4x4::GlmFromMatrix4x4(Matrix4x4::Identity());
        glm::mat4 rotation4Matrix = Matrix4x4::GlmFromMatrix4x4(rotationMatrix);

        auto transformMatrix = inProjectionMatrix
                      * glm::translate(identityMatrix, glm::vec3(Position.X, Position.Y, Position.Z))
                      * rotation4Matrix
                      * glm::scale(identityMatrix, glm::vec3(Scale.X, Scale.Y, Scale.Z));
        //    TransformMatrix = inProjectionMatrix
        //                      * glm::translate(IdentityMatrix, glm::vec3(Position.X, Position.Y, Position.Z))
        //                      * glm::rotate(IdentityMatrix, glm::radians(RotationDegrees), RotationAxis)
        //                      * glm::scale(IdentityMatrix, glm::vec3(Scale.X, Scale.Y, Scale.Z));

        TransformMatrix = Matrix4x4::Matrix4X4FromGlm(transformMatrix);
    }

    void Transform::OnEulerReflect() {
        // TODO: Use Quaternion.Rotate or we would create gimble lock issues
        Quat = Quaternion(Euler);
    }

    Matrix4x4 Transform::LookAtRH(Vector3 position, Vector3 target, Vector3 up) {
        const auto positionGLM = Vector3::GlmFromVector3(position);
        const auto targetGLM = Vector3::GlmFromVector3(target);
        const auto upGLM = Vector3::GlmFromVector3(up);

        return Matrix4x4::Matrix4X4FromGlm(glm::lookAtLH(positionGLM, targetGLM, upGLM));
    }
}
