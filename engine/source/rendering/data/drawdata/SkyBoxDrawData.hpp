//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_SKYBOXDRAWDATA_HPP
#define MEOWENGINE_SKYBOXDRAWDATA_HPP

namespace MeowEngine::Rendering {
    struct SkyBoxDrawData {
        Asset::AssetHandle VertexShader;
        Asset::AssetHandle FragmentShader;

        glm::mat4 TransformMatrix;
    };
}

#endif //MEOWENGINE_SKYBOXDRAWDATA_HPP