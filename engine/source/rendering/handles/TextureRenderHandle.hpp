//
// Created by Akira Mujawar on 21/05/26.
//

#ifndef MEOWENGINE_TEXTURERENDEREHANDLE_HPP
#define MEOWENGINE_TEXTURERENDEREHANDLE_HPP

#include <IRenderHandle.hpp>

namespace MeowEngine::Rendering {
    struct TextureRenderHandle : IRenderHandle {
        TextureRenderHandle();
        ~TextureRenderHandle() override;

    private:
        Asset::AssetHandle BitmapAsset;
    };
}

#endif //MEOWENGINE_TEXTURERENDEREHANDLE_HPP