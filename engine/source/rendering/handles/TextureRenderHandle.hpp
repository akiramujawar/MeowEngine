//
// Created by Akira Mujawar on 21/05/26.
//

#ifndef MEOWENGINE_TEXTURERENDEREHANDLE_HPP
#define MEOWENGINE_TEXTURERENDEREHANDLE_HPP

#include <IRenderHandle.hpp>

namespace MeowEngine::Rendering {
    struct TextureRenderHandle : IRenderHandle {
        TextureRenderHandle() = default;
        TextureRenderHandle(const Asset::AssetHandle& bitmap) {
            BitmapAsset = bitmap;
        }

        ~TextureRenderHandle() override = default;

        bool operator==(const TextureRenderHandle& handle) const {
            return BitmapAsset == handle.BitmapAsset;
        }

        bool operator!=(const TextureRenderHandle& handle) const {
            return !(*this == handle);
        }

        bool IsValid() override { return BitmapAsset.GetIsValid(); };

        Asset::AssetHandle BitmapAsset;
    };
}

namespace std {
    template<>
    struct hash<MeowEngine::Rendering::TextureRenderHandle> {
        std::size_t operator()(const MeowEngine::Rendering::TextureRenderHandle& handle) const noexcept {
            auto const hash = std::hash<uint64_t>()(handle.BitmapAsset.GetUUID());

            return hash;
        }
    };
}

#endif //MEOWENGINE_TEXTURERENDEREHANDLE_HPP