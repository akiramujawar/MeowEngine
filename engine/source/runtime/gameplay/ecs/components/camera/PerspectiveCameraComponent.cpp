//
// Created by Akira Mujawar on 26/01/26.
//

#include "PerspectiveCameraComponent.hpp"


namespace  MeowEngine::Runtime {
    void PerspectiveCameraComponent::Reflect() {
        REGISTER_PROPERTY(PerspectiveCameraComponent, Local, Transform, true, true);

        REGISTER_PROPERTY(PerspectiveCameraComponent, Width, float, true, false);
        REGISTER_PROPERTY(PerspectiveCameraComponent, Height, float, true, false);

        REGISTER_PROPERTY(PerspectiveCameraComponent, Near, float, true, false);
        REGISTER_PROPERTY(PerspectiveCameraComponent, Far, float, true, false);
    }

    void PerspectiveCameraComponent::UpdateMatrix() {
        ViewMatrix = MatrixTransform::LookAtRH(Local.Position, Local.Position + Local.Forward, Local.Up);

        auto projection = Matrix4x4::GlmFromMatrix4x4(ProjectionMatrix);
        auto view = Matrix4x4::GlmFromMatrix4x4(ViewMatrix);
        auto projectionview = projection * view;
        // ProjectionViewMatrix = ProjectionMatrix * ViewMatrix;
        ProjectionViewMatrix = Matrix4x4::Matrix4X4FromGlm(projectionview);

        // MeowEngine::Log("ViewMatrix", ViewMatrix.GetString());
    }

    void PerspectiveCameraComponent::SetViewport(float width, float height) {
        Width = width;
        Height = height;
        ProjectionMatrix = MatrixClip::PerspectiveLH_NO(45 * PI / 180, width/height, Near, Far);
    }


}
