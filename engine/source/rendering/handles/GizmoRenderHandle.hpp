//
// Created by Akira Mujawar on 01/07/26.
//

#ifndef MEOWENGINE_GIZMORENDERHANDLE_HPP
#define MEOWENGINE_GIZMORENDERHANDLE_HPP

#include <IRenderHandle.hpp>

namespace MeowEngine::Rendering {
    struct GizmoRenderHandle : IRenderHandle {
        GizmoRenderHandle() = default;
        GizmoRenderHandle(const Asset::AssetHandle& bitmap) {
            Asset = bitmap;
        }

        ~GizmoRenderHandle() override = default;

        bool operator==(const GizmoRenderHandle& handle) const {
            return Asset == handle.Asset;
        }

        bool operator!=(const GizmoRenderHandle& handle) const {
            return !(*this == handle);
        }

        bool IsValid() const override { return Asset.GetIsValid(); };

        Asset::AssetHandle Asset;
    };
}

namespace std {
    template<>
    struct hash<MeowEngine::Rendering::GizmoRenderHandle> {
        std::size_t operator()(const MeowEngine::Rendering::GizmoRenderHandle& handle) const noexcept {
            auto const hash = std::hash<uint64_t>()(handle.Asset.GetUUID());

            return hash;
        }
    };
}

#endif //MEOWENGINE_GIZMORENDERHANDLE_HPP