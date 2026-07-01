//
// Created by Akira Mujawar on 26/01/26.
//

#include "CameraComponent.hpp"


namespace  MeowEngine::Runtime {
    void CameraComponent::Reflect() {
        REGISTER_PROPERTY(CameraComponent, Local, Transform, true, true);

        // REGISTER_PROPERTY(CameraComponent, Width, float, true, false);
        // REGISTER_PROPERTY(CameraComponent, Height, float, true, false);

        REGISTER_PROPERTY(CameraComponent, Near, float, true, false);
        REGISTER_PROPERTY(CameraComponent, Far, float, true, false);
        REGISTER_PROPERTY(CameraComponent, MoveSpeed, float, true, false);
        REGISTER_PROPERTY(CameraComponent, LookAroundSpeed, float, true, false);
    }

    void CameraComponent::UpdateMatrix() {
        View = Transform::LookAt(GetPosition(), GetPosition() + GetForward(), GetUp());
        // NOTE: quick hack to fix coordinate system
        // as we use perspectiveRH_NO & lookAtRH
        Matrix4x4 flipZ = Matrix4x4::Identity();
        flipZ[0][0] = -1.0f;
        flipZ[1][1] = -1.0f;
        flipZ[2][2] = -1.0f;
        View = View * flipZ;

        ViewProjection = Projection * View;
    }

    void CameraComponent::SetViewport(float width, float height) {
        Projection = MatrixClip::Perspective(45 * PI / 180, width/height, Near, Far);
    }


}
