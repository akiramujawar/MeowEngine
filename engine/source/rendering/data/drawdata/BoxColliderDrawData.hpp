//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_BOXCOLLIDERDRAWDATA_HPP
#define MEOWENGINE_BOXCOLLIDERDRAWDATA_HPP

namespace MeowEngine::Rendering {
    struct BoxColliderDrawData {
        Asset::AssetHandle VertexShader;
        Asset::AssetHandle FragmentShader;

        glm::mat4 TransformMatrix;
    };
}

#endif //MEOWENGINE_BOXCOLLIDERDRAWDATA_HPP