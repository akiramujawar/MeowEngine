//
// Created by Akira Mujawar on 03/07/24.
//

#include "Transform3DComponent.hpp"
#include <log.hpp>

namespace MeowEngine::Runtime {
    void Transform3DComponent::Reflect() {
        REGISTER_PROPERTY(Transform3DComponent, Local, Transform, true, true);
    }

    // void Transform3DComponent::Update(const float& deltaTime) {
        // NOTE: Testing. Need to achieve through macro + reflection
        //    Rotation = math::Quaternion(Euler.X * M_PI / 180, Euler.Y* M_PI / 180, Euler.Z* M_PI / 180);
        //    float random = (float)std::rand() / RAND_MAX;
        //    Position.Y += 1.2f * deltaTime;
        //    Euler.X += 1.2f * deltaTime;
        //    RecalculateQuaternion();

        //    Rotation.Rotate(10.0f * deltaTime, 13.0f * deltaTime, 13.0f * deltaTime);
        //    RecalculateEuler();
    // }

}