//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_SKYBOXDRAWDATA_HPP
#define MEOWENGINE_SKYBOXDRAWDATA_HPP

#include <ShaderRenderHandle.hpp>
#include <glm/glm.hpp>

namespace MeowEngine::Rendering {
    struct SkyboxDrawData {
        ShaderRenderHandle Shader;

        glm::mat4 TransformMatrix;
    };
}

#endif //MEOWENGINE_SKYBOXDRAWDATA_HPP