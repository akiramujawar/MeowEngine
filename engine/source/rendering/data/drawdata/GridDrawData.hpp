//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_GRIDDRAWDATA_HPP
#define MEOWENGINE_GRIDDRAWDATA_HPP

namespace MeowEngine::Rendering {
    // NOTE: this goes to renderer pass config hence
    // NOTE: we don't need a component or entity or draw data for this
    struct GridDrawData {
        Asset::AssetHandle VertexShader;
        Asset::AssetHandle FragmentShader;

        glm::mat4 TransformMatrix;
    };
}

#endif //MEOWENGINE_GRIDDRAWDATA_HPP