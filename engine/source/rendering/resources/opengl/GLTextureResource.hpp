//
// Created by Akira Mujawar on 20/06/24.
//

#ifndef MEOWENGINE_GLTEXTURERESOURCE_HPP
#define MEOWENGINE_GLTEXTURERESOURCE_HPP

#pragma once

// #include "bitmap.hpp"
// #include "internal_ptr.hpp"

#include <AssetHandle.hpp>

namespace MeowEngine::Rendering {
    struct GLTextureResource {
        // GLTextureResource(const MeowEngine::Bitmap& bitmap);
        GLTextureResource(Asset::AssetHandle handle);
        ~GLTextureResource();

        // need to call whenever we want the texture to be applied to the object being rendered
        void Bind() const;

    private:
        uint32_t TextureID;
        // MeowEngine::internal_ptr<Internal> InternalPointer;
    };
}

#endif //MEOWENGINE_GLTEXTURERESOURCE_HPP
