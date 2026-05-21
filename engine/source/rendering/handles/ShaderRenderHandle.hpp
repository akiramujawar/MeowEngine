//
// Created by Akira Mujawar on 19/05/26.
//

#ifndef MEOWENGINE_SHADERRENDERHANDLE_HPP
#define MEOWENGINE_SHADERRENDERHANDLE_HPP

// combo of 2 asset handles
// .frag & .vert
#include <IRenderHandle.hpp>

namespace MeowEngine::Rendering {
    struct ShaderRenderHandle : IRenderHandle {
        ShaderRenderHandle();
        ~ShaderRenderHandle() override;

    private:
        Asset::AssetHandle VertexAsset;
        Asset::AssetHandle FragmentAsset;
    };
}

#endif //MEOWENGINE_SHADERRENDERHANDLE_HPP