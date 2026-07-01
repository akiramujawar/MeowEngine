//
// Created by Akira Mujawar on 20/06/24.
//

#include "GLTextureResource.hpp"
#include "GL_API.hpp"
#include "MeowService.hpp"
#include "AssetManager.hpp"
#include "BitmapAsset.hpp"

// using MeowEngine::GLTextureResource;
//
namespace {
    using MeowEngine::Asset::BitmapAsset;

    GLuint CreateTexture(const BitmapAsset& bitmap) {
        GLuint TextureID;

        glGenTextures(1, &TextureID);
        glBindTexture(GL_TEXTURE_2D, TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            bitmap.GetWidth(),
            bitmap.GetHeight(),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            bitmap.GetPixelData()
        );

        return TextureID;
    }
} // namespace
//
// struct GLTextureResource::Internal {
//     const GLuint TextureID;
//
//     Internal(const MeowEngine::Bitmap& bitmap)
//         : TextureID(::CreateTexture(bitmap)) {}
//
//     ~Internal() {
//         glDeleteTextures(1, &TextureID);
//     }
// };
//
// GLTextureResource::GLTextureResource(const MeowEngine::Bitmap &bitmap)
//     : InternalPointer(MeowEngine::make_internal_ptr<Internal>(bitmap)){}
//
// void GLTextureResource::Bind() const {
//     glBindTexture(GL_TEXTURE_2D, InternalPointer->TextureID);
// }

namespace MeowEngine::Rendering {
    GLTextureResource::GLTextureResource(Asset::AssetHandle handle) {
        auto* asset = MeowService().AssetManager.GetAsset<Asset::BitmapAsset>(handle);

        TextureID = CreateTexture(*asset);
    }

    GLTextureResource::~GLTextureResource() {
        glDeleteTextures(1, &TextureID);
    }

    void GLTextureResource::Bind() const {
        glBindTexture(GL_TEXTURE_2D, TextureID);
    }
}
