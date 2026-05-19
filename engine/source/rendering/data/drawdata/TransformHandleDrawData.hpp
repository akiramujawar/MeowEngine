//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_TRANSFORMHANDLEDRAWDATA_HPP
#define MEOWENGINE_TRANSFORMHANDLEDRAWDATA_HPP

namespace MeowEngine::Rendering {
    struct TransformHandleDrawData {
        Asset::AssetHandle VertexShader;
        Asset::AssetHandle FragmentShader;

        glm::mat4 TransformMatrix;
    };
}

#endif //MEOWENGINE_TRANSFORMHANDLEDRAWDATA_HPP