//
// Created by Akira Mujawar on 27/02/26.
//

#ifndef MEOWENGINE_OPENGL_THUMBNAIL_HPP
#define MEOWENGINE_OPENGL_THUMBNAIL_HPP

#pragma once

#include "bitmap.hpp"
#include "internal_ptr.hpp"

namespace MeowEngine {
    struct OpenGLThumbnail {
        OpenGLThumbnail(const MeowEngine::Bitmap& bitmap);

        // need to call whenever we want the texture to be applied to the object being rendered
        void Bind() const;
        u_int16_t GetWidth() const;
        u_int16_t GetHeight() const;
        void* GetTextureID() const;

    private:
        struct Internal;
        MeowEngine::internal_ptr<Internal> InternalPointer;
    };
}



#endif //MEOWENGINE_OPENGL_THUMBNAIL_HPP
