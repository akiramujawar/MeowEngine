//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_TRANSFORMHANDLEDRAWDATA_HPP
#define MEOWENGINE_TRANSFORMHANDLEDRAWDATA_HPP

#include <ShaderRenderHandle.hpp>
#include <GLM_API.hpp>

namespace MeowEngine::Rendering {
    struct TransformHandleDrawData {
        ShaderRenderHandle Shader;

        glm::mat4 TransformMatrix;
    };
}

#endif //MEOWENGINE_TRANSFORMHANDLEDRAWDATA_HPP