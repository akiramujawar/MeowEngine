//
// Created by Akira Mujawar on 03/07/24.
//

#include "transform3d_component.hpp"
#include <log.hpp>

#include "reflection_macro_wrapper.hpp"

using MeowEngine::entity::Transform3DComponent;

void MeowEngine::entity::Transform3DComponent::Reflect() {
    REGISTER_PROPERTY(Transform3DComponent, Position, MeowEngine::math::Vector3, true);
    REGISTER_PROPERTY(Transform3DComponent, Scale, MeowEngine::math::Vector3, true);
    REGISTER_PROPERTY(Transform3DComponent, Quaternion, MeowEngine::math::Quaternion, false);
    REGISTER_PROPERTY_CALLBACK(Transform3DComponent, Rotation, MeowEngine::math::Vector3, true, OnRotationReflect);
}

Transform3DComponent::Transform3DComponent(const glm::mat4& inProjectionMatrix)
    : Position({0,0,0})
    , Scale ({1,1,1})

    , IdentityMatrix(glm::mat4(1.0f))
    , TransformMatrix(IdentityMatrix) {
    CalculateTransformMatrix(inProjectionMatrix);
}

Transform3DComponent::Transform3DComponent(const glm::mat4& inProjectionMatrix, MeowEngine::math::Vector3 position, MeowEngine::math::Vector3 scale, MeowEngine::math::Quaternion rotation)
    : Position(position)
    , Scale(scale)
    , Quaternion(rotation)
    , IdentityMatrix(glm::mat4(1.0f))
    , TransformMatrix(IdentityMatrix) {
    CalculateTransformMatrix(inProjectionMatrix);
}

Transform3DComponent::Transform3DComponent(const glm::mat4& inProjectionMatrix, MeowEngine::math::Vector3 position, MeowEngine::math::Vector3 scale, MeowEngine::math::Vector3 eulerRotation)
        : Position(position)
        , Scale(scale)
        , Quaternion(eulerRotation)

        , IdentityMatrix(glm::mat4(1.0f))
        , TransformMatrix(IdentityMatrix) {
    CalculateTransformMatrix(inProjectionMatrix);
}

Transform3DComponent::Transform3DComponent(const glm::mat4& inProjectionMatrix, MeowEngine::math::Vector3 position, MeowEngine::math::Vector3 scale, glm::vec3 rotationAxis,
                                           float rotationDegrees)
    : Position(position)
    , Scale(scale)

    , IdentityMatrix(glm::mat4(1.0f))
    , TransformMatrix(IdentityMatrix) {
    CalculateTransformMatrix(inProjectionMatrix);
}

void Transform3DComponent::CalculateTransformMatrix(const glm::mat4 &inProjectionMatrix) {
    math::Matrix4x4 rotationMatrix = Quaternion.GetRotationMatrix4x4();
    // TODO: Implement full matrix structure for transform matrix
    glm::mat4 rotation4Matrix {};
    rotation4Matrix[0][0] = rotationMatrix.X1;
    rotation4Matrix[0][1] = rotationMatrix.Y1;
    rotation4Matrix[0][2] = rotationMatrix.Z1;
    rotation4Matrix[0][3] = rotationMatrix.D1;

    rotation4Matrix[1][0] = rotationMatrix.X2;
    rotation4Matrix[1][1] = rotationMatrix.Y2;
    rotation4Matrix[1][2] = rotationMatrix.Z2;
    rotation4Matrix[1][3] = rotationMatrix.D2;

    rotation4Matrix[2][0] = rotationMatrix.X3;
    rotation4Matrix[2][1] = rotationMatrix.Y3;
    rotation4Matrix[2][2] = rotationMatrix.Z3;
    rotation4Matrix[2][3] = rotationMatrix.D3;

    rotation4Matrix[3][0] = rotationMatrix.X4;
    rotation4Matrix[3][1] = rotationMatrix.Y4;
    rotation4Matrix[3][2] = rotationMatrix.Z4;
    rotation4Matrix[3][3] = rotationMatrix.D4;

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
//    Quaternion = math::Quaternion(Rotation.X * M_PI / 180, Rotation.Y* M_PI / 180, Rotation.Z* M_PI / 180);
//    float random = (float)std::rand() / RAND_MAX;
//    Position.Y += 1.2f * deltaTime;

//    RotateBy(1.0f * 0.2f);
}

void Transform3DComponent::OnRotationReflect() {
    Quaternion = math::Quaternion(Rotation.X * M_PI / 180, Rotation.Y* M_PI / 180, Rotation.Z * M_PI / 180);
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