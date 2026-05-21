//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_MESHDRAWDATA_HPP
#define MEOWENGINE_MESHDRAWDATA_HPP

#include <GLM_API.hpp>
#include <ShaderRenderHandle.hpp>
#include <MeshRenderHandle.hpp>
#include <TextureRenderHandle.hpp>

namespace MeowEngine::Rendering {
    struct MeshDrawData {
        ShaderRenderHandle Shader;
        MeshRenderHandle Mesh;
        TextureRenderHandle Texture;

        glm::mat4 TransformMatrix;
    };
}

#endif //MEOWENGINE_MESHDRAWDATA_HPP