//
// Created by Akira Mujawar on 21/05/26.
//

#ifndef MEOWENGINE_MESHRENDERHANDLE_HPP
#define MEOWENGINE_MESHRENDERHANDLE_HPP

#include <IRenderHandle.hpp>

namespace MeowEngine::Rendering {
    struct MeshRenderHandle : IRenderHandle {
        MeshRenderHandle() = default;
        MeshRenderHandle(const Asset::AssetHandle& mesh) {
            MeshAsset = mesh;
        }

        ~MeshRenderHandle() override = default;

        bool operator==(const MeshRenderHandle& handle) const {
            return MeshAsset == handle.MeshAsset;
        }

        bool operator!=(const MeshRenderHandle& handle) const {
            return !(*this == handle);
        }

        Asset::AssetHandle MeshAsset;
    };
}

namespace std {
    template<>
    struct hash<MeowEngine::Rendering::MeshRenderHandle> {
        std::size_t operator()(const MeowEngine::Rendering::MeshRenderHandle& handle) const noexcept {
            auto const hash = std::hash<uint64_t>()(handle.MeshAsset.GetUUID());

            return hash;
        }
    };
}

#endif //MEOWENGINE_MESHRENDERHANDLE_HPP