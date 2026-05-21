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
        ShaderRenderHandle() = default;
        ShaderRenderHandle(const Asset::AssetHandle& vertex, const Asset::AssetHandle& fragment) {
            VertexAsset = vertex;
            FragmentAsset = fragment;
        }

        ~ShaderRenderHandle() override = default;

        bool operator==(const ShaderRenderHandle& handle) const {
            return VertexAsset == handle.VertexAsset && FragmentAsset == handle.FragmentAsset;
        }

        bool operator!=(const ShaderRenderHandle& handle) const {
            return !(*this == handle);
        }

        Asset::AssetHandle VertexAsset;
        Asset::AssetHandle FragmentAsset;
    };
}

namespace std {
    template<>
    struct hash<MeowEngine::Rendering::ShaderRenderHandle> {
        std::size_t operator()(const MeowEngine::Rendering::ShaderRenderHandle& handle) const noexcept {
            auto const vertexHash = std::hash<uint64_t>()(handle.VertexAsset.GetUUID());
            auto const fragmentHash = std::hash<uint64_t>()(handle.FragmentAsset.GetUUID());

            return vertexHash ^ (fragmentHash << 1);
        }
    };
}

#endif //MEOWENGINE_SHADERRENDERHANDLE_HPP