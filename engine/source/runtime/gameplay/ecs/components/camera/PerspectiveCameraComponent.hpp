//
// Created by Akira Mujawar on 26/01/26.
//

#ifndef MEOWENGINE_PERSPECTIVE_CAMERA_COMPONENT_HPP
#define MEOWENGINE_PERSPECTIVE_CAMERA_COMPONENT_HPP

#include "IComponent.hpp"
#include "transform3d_component.hpp"
#include "Math.hpp"

namespace MeowEngine::Runtime {
    class PerspectiveCameraComponent : public Transform3DComponent {
    public:
        REFLECT_COMPONENT(PerspectiveCameraComponent)
        static void Reflect();

        PerspectiveCameraComponent() = default;
        ~PerspectiveCameraComponent() override = default;

        void UpdateMatrix();

        [[nodiscard]] Matrix4x4 GetProjectionMatrix() const { return ProjectionMatrix;};
        [[nodiscard]] Matrix4x4 GetViewMatrix() const { return ViewMatrix;};
        [[nodiscard]] Matrix4x4 GetProjectionViewMatrix () const { return ProjectionViewMatrix;};

        // void SetLookAt(Vector3 direction);
        // void LookAroundDelta(const float& deltaX, const float& deltaY);

        void OnUpReflect();
        void OnForwardReflect();
        void SetViewport(float width, float height);

    private:
        Matrix4x4 ProjectionMatrix;
        Matrix4x4 ViewMatrix;
        Matrix4x4 ProjectionViewMatrix;

        float Width = 100;
        float Height = 100;
        float Near = 0.1f;
        float Far = 3000;
    };
}


#endif //MEOWENGINE_PERSPECTIVE_CAMERA_COMPONENT_HPP
