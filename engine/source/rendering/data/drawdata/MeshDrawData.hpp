//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_MESHDRAWDATA_HPP
#define MEOWENGINE_MESHDRAWDATA_HPP

#include <AssetHandle.hpp>
#include <GLM_API.hpp>

namespace MeowEngine::Rendering {
    struct MeshDrawData {
        Asset::AssetHandle VertexShader;
        Asset::AssetHandle FragmentShader;
        Asset::AssetHandle Mesh;

        glm::mat4 TransformMatrix;
    };
}

#endif //MEOWENGINE_MESHDRAWDATA_HPP