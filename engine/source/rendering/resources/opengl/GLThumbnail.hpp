//
// Created by Akira Mujawar on 27/02/26.
//

#ifndef MEOWENGINE_OPENGL_THUMBNAIL_HPP
#define MEOWENGINE_OPENGL_THUMBNAIL_HPP

#pragma once

// #include "Bitmap.hpp"
// #include "internal_ptr.hpp"
#include <AssetHandle.hpp>

namespace MeowEngine::Rendering {
    struct OpenGLThumbnail {
        OpenGLThumbnail(Asset::AssetHandle handle);

        // need to call whenever we want the texture to be applied to the object being rendered
        void Bind() const;

        [[nodiscard]] uint16_t GetWidth() const { return Width; }
        [[nodiscard]] uint16_t GetHeight() const { return Height; }
        [[nodiscard]] void* GetTextureID() const { return reinterpret_cast<void*>(static_cast<intptr_t>(TextureID)); }

    private:
        uint32_t TextureID;
        uint16_t Width;
        uint16_t Height;

    // private:
    //     struct Internal;
    //     MeowEngine::internal_ptr<Internal> InternalPointer;
    };
}



#endif //MEOWENGINE_OPENGL_THUMBNAIL_HPP
