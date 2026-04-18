//
// Created by Akira Mujawar on 03/07/24.
//

#include "transform3d_component.hpp"
#include <log.hpp>
#include "glm_extension.hpp"

#include "reflection_macro_wrapper.hpp"

using MeowEngine::entity::Transform3DComponent;

void MeowEngine::entity::Transform3DComponent::Reflect() {
    REGISTER_PROPERTY(Transform3DComponent, Position, Vector3, true, true);
    REGISTER_PROPERTY(Transform3DComponent, Scale, Vector3, true, true);
    REGISTER_PROPERTY(Transform3DComponent, Rotation, Quaternion, false, true);
    REGISTER_PROPERTY_CALLBACK(Transform3DComponent, Euler, Vector3, true, true, OnRotationReflect);
}

Transform3DComponent::Transform3DComponent(const glm::mat4& inProjectionMatrix)
    : Position({0,0,0})
    , Scale ({1,1,1})

    , IdentityMatrix(glm::mat4(1.0f))
    , TransformMatrix(IdentityMatrix) {
    CalculateTransformMatrix(inProjectionMatrix);
}

Transform3DComponent::Transform3DComponent(const glm::mat4& inProjectionMatrix, Vector3 position, Vector3 scale, Quaternion rotation)
    : Position(position)
    , Scale(scale)
    , Rotation(rotation)
    , IdentityMatrix(glm::mat4(1.0f))
    , TransformMatrix(IdentityMatrix) {
    CalculateTransformMatrix(inProjectionMatrix);
}

Transform3DComponent::Transform3DComponent(const glm::mat4& inProjectionMatrix, Vector3 position, Vector3 scale, Vector3 eulerRotation)
        : Position(position)
        , Scale(scale)
        , Rotation(eulerRotation)

        , IdentityMatrix(glm::mat4(1.0f))
        , TransformMatrix(IdentityMatrix) {
    CalculateTransformMatrix(inProjectionMatrix);
}

Transform3DComponent::Transform3DComponent(const glm::mat4& inProjectionMatrix, Vector3 position, Vector3 scale, glm::vec3 rotationAxis,
                                           float rotationDegrees)
    : Position(position)
    , Scale(scale)

    , IdentityMatrix(glm::mat4(1.0f))
    , TransformMatrix(IdentityMatrix) {
    CalculateTransformMatrix(inProjectionMatrix);
}

void Transform3DComponent::CalculateTransformMatrix(const glm::mat4 &inProjectionMatrix) {
    Matrix4x4 rotationMatrix = Rotation.GetRotationMatrix4x4();
    glm::mat4 rotation4Matrix = MeowEngine::GLMExtension::GetMat4FromMatrix4x4(rotationMatrix);

        TransformMatrix = inProjectionMatrix
                      * glm::translate(IdentityMatrix, glm::vec3(Position.X, Position.Y, Position.Z))
                      * rotation4Matrix
                      * glm::scale(IdentityMatrix, glm::vec3(Scale.X, Scale.Y, Scale.Z));
//    TransformMatrix = inProjectionMatrix
//                      * glm::translate(IdentityMatrix, glm::vec3(Position.X, Position.Y, Position.Z))
//                      * glm::rotate(IdentityMatrix, glm::radians(RotationDegrees), RotationAxis)
//                      * glm::scale(IdentityMatrix, glm::vec3(Scale.X, Scale.Y, Scale.Z));
}

void Transform3DComponent::Update(const float& deltaTime) {
    // NOTE: Testing. Need to achieve through macro + reflection
//    Rotation = math::Quaternion(Euler.X * M_PI / 180, Euler.Y* M_PI / 180, Euler.Z* M_PI / 180);
//    float random = (float)std::rand() / RAND_MAX;
//    Position.Y += 1.2f * deltaTime;
//    Euler.X += 1.2f * deltaTime;
//    RecalculateQuaternion();

//    Rotation.Rotate(10.0f * deltaTime, 13.0f * deltaTime, 13.0f * deltaTime);
//    RecalculateEuler();
}

void Transform3DComponent::RecalculateEuler() {
    Euler = Quaternion::Euler(Rotation);
}

void Transform3DComponent::OnRotationReflect() {
    // TODO: Use Quaternion.Rotate or we would create gimble lock issues
    Rotation = Quaternion(Euler);
}

//void Transform3DComponent::RotateBy(const float &degrees) {
//    RotationDegrees += degrees;
//
//    if(RotationDegrees > 360.0f) {
//        RotationDegrees -= 360.0f;
//    }
//    else if(RotationDegrees < -360.0f) {
//        RotationDegrees += 360;
//    }
//}