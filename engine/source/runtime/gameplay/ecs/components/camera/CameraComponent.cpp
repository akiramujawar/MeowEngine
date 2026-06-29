//
// Created by Akira Mujawar on 26/01/26.
//

#include "CameraComponent.hpp"


namespace  MeowEngine::Runtime {
    void CameraComponent::Reflect() {
        REGISTER_PROPERTY(CameraComponent, Local, Transform, true, true);

        REGISTER_PROPERTY(CameraComponent, Width, float, true, false);
        REGISTER_PROPERTY(CameraComponent, Height, float, true, false);

        REGISTER_PROPERTY(CameraComponent, Near, float, true, false);
        REGISTER_PROPERTY(CameraComponent, Far, float, true, false);
    }

    void CameraComponent::UpdateMatrix() {
        View = Transform::LookAtRH(Local.GetPosition(), Local.GetPosition() + Local.GetForward(), Local.GetUp());

        ViewProjection = Projection * View;
    }

    void CameraComponent::SetViewport(float width, float height) {
        Width = width;
        Height = height;

        Projection = MatrixClip::PerspectiveLH_NO(45 * PI / 180, width/height, Near, Far);
    }


}
