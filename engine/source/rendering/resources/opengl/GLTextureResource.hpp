//
// Created by Akira Mujawar on 20/06/24.
//

#ifndef MEOWENGINE_GLTEXTURERESOURCE_HPP
#define MEOWENGINE_GLTEXTURERESOURCE_HPP

#pragma once

#include "bitmap.hpp"
#include "internal_ptr.hpp"

namespace MeowEngine {
    struct GLTextureResource {
        GLTextureResource(const MeowEngine::Bitmap& bitmap);

        // need to call whenever we want the texture to be applied to the object being rendered
        void Bind() const;

    private:
        struct Internal;
        MeowEngine::internal_ptr<Internal> InternalPointer;
    };
}

#endif //MEOWENGINE_GLTEXTURERESOURCE_HPP
