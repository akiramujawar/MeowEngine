//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_SPHERECOLLIDERDRAWDATA_HPP
#define MEOWENGINE_SPHERECOLLIDERDRAWDATA_HPP

namespace MeowEngine::Rendering {
    struct SphereColliderDrawData {
        Asset::AssetHandle VertexShader;
        Asset::AssetHandle FragmentShader;

        glm::mat4 TransformMatrix;
    };
}

#endif //MEOWENGINE_SPHERECOLLIDERDRAWDATA_HPP