//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_TRANSFORMHANDLEDRAWDATA_HPP
#define MEOWENGINE_TRANSFORMHANDLEDRAWDATA_HPP

#include "Math.hpp"
#include "ShaderRenderHandle.hpp"
#include "GizmoRenderHandle.hpp"

namespace MeowEngine::Rendering {
    struct TransformGizmoDrawData {
        ShaderRenderHandle Shader;
        GizmoRenderHandle Gizmo;

        Vector3 CameraPosition;
        Matrix4x4 ViewMatrix;
        Matrix4x4 ProjectionMatrix;

        Vector3 SelfPosition;
        Matrix4x4 RotationMatrix;
    };
}

#endif //MEOWENGINE_TRANSFORMHANDLEDRAWDATA_HPP