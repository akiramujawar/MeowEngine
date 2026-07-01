//
// Created by Akira Mujawar on 27/02/26.
//

#include "GLThumbnail.hpp"

#include "GL_API.hpp"
#include "log.hpp"
#include "MeowService.hpp"
#include "AssetManager.hpp"
#include "BitmapAsset.hpp"

namespace {
    GLuint CreateTexture(const MeowEngine::Asset::BitmapAsset& bitmap) {
        GLuint TextureID;

        glGenTextures(1, &TextureID);
        glBindTexture(GL_TEXTURE_2D, TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA8,
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

namespace MeowEngine::Rendering {
    OpenGLThumbnail::OpenGLThumbnail(Asset::AssetHandle handle) {
        auto* asset = MeowService().AssetManager.GetAsset<Asset::BitmapAsset>(handle);
        TextureID = ::CreateTexture(*asset);
        Width = asset->GetWidth();
        Height = asset->GetHeight();
    }

    void OpenGLThumbnail::Bind() const {
        glBindTexture(GL_TEXTURE_2D, TextureID);
    }
}

// struct MeowEngine::OpenGLThumbnail::Internal {
     // const GLuint TextureID;
//     const uint16_t Width;
//     const uint16_t Height;
//
//     Internal(const Asset::Bitmap& bitmap)
//         : TextureID(::CreateTexture(bitmap))
//         , Width(bitmap.GetWidth())
//         , Height(bitmap.GetHeight()) {
//     }
//
//     ~Internal() {
//         glDeleteTextures(1, &TextureID);
//     }
// };
//
// MeowEngine::OpenGLThumbnail::OpenGLThumbnail(const Asset::Bitmap &bitmap)
//     : InternalPointer(MeowEngine::make_internal_ptr<Internal>(bitmap)){}
//
// void MeowEngine::OpenGLThumbnail::Bind() const {
//     glBindTexture(GL_TEXTURE_2D, InternalPointer->TextureID);
// }
//
// uint16_t MeowEngine::OpenGLThumbnail::GetWidth() const {
//     return InternalPointer->Width;
// }
//
// uint16_t MeowEngine::OpenGLThumbnail::GetHeight() const {
//     return InternalPointer->Height;
// }
//
// void* MeowEngine::OpenGLThumbnail::GetTextureID() const {
//     return (void*)(intptr_t)InternalPointer->TextureID;
// }