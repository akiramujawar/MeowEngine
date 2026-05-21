//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_SPHERECOLLIDERDRAWDATA_HPP
#define MEOWENGINE_SPHERECOLLIDERDRAWDATA_HPP

#include <ShaderRenderHandle.hpp>
#include <GLM_API.hpp>

namespace MeowEngine::Rendering {
    struct SphereColliderDrawData {
        ShaderRenderHandle Shader;

        glm::mat4 TransformMatrix;
    };
}

#endif //MEOWENGINE_SPHERECOLLIDERDRAWDATA_HPP