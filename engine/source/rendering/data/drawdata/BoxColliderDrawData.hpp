//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_BOXCOLLIDERDRAWDATA_HPP
#define MEOWENGINE_BOXCOLLIDERDRAWDATA_HPP

#include <ShaderRenderHandle.hpp>

namespace MeowEngine::Rendering {
    struct BoxColliderDrawData {
        ShaderRenderHandle Shader;

        glm::mat4 TransformMatrix;
    };
}

#endif //MEOWENGINE_BOXCOLLIDERDRAWDATA_HPP