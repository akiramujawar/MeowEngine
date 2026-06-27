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

    Transform::Transform() {
        Up = Vector3(0.0f, 1.0f, 0.0f);
        Forward = Vector3(0.0f, 0.0f, 1.0f);
    }

    void Transform::SetEuler(const Vector3& euler) {
        Euler = euler;
        Quat = Quaternion(euler);
    }

    void Transform::SetQuaternion(const Quaternion& quat) {
        Quat = quat;
        Euler = Quaternion::Euler(quat);
    }

    void Transform::CalculateTransformMatrix(const glm::mat4& inProjectionMatrix) {
        Matrix4x4 rotationMatrix = Quat.GetRotationMatrix4x4();

        glm::mat4x4 identityMatrix =  Matrix4x4::GlmFromMatrix4x4(Matrix4x4::Identity());
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
}
