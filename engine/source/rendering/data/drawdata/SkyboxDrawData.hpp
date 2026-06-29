//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_SKYBOXDRAWDATA_HPP
#define MEOWENGINE_SKYBOXDRAWDATA_HPP

#include <ShaderRenderHandle.hpp>
#include "Math.hpp"


namespace MeowEngine::Rendering {
    struct SkyboxDrawData {
        ShaderRenderHandle Shader;

        Matrix4x4 CameraViewMatrix;
        Matrix4x4 CameraProjectionMatrix;
    };
}

#endif //MEOWENGINE_SKYBOXDRAWDATA_HPP