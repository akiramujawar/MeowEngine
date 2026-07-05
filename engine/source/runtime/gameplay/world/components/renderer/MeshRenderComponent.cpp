//
// Created by Akira Mujawar on 23/06/24.
//

#include "MeshRenderComponent.hpp"
#include <log.hpp>

using MeowEngine::Runtime::MeshRenderComponent;

namespace MeowEngine::Runtime {
    using Asset::AssetHandle;

    void MeshRenderComponent::Reflect() {
        REGISTER_PROPERTY(MeshRenderComponent, ShaderAssetHandle, AssetHandle, true, false);
        REGISTER_PROPERTY(MeshRenderComponent, MeshAssetHandle, AssetHandle, true, false);
        REGISTER_PROPERTY(MeshRenderComponent, TextureAssetHandle, AssetHandle, true, false);
    }
}