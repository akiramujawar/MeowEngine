//
// Created by Akira Mujawar on 06/07/26.
//

#include "MeshColliderComponent.hpp"

namespace MeowEngine::Runtime {
    using Asset::AssetHandle;

    void MeshColliderComponent::Reflect() {
        REGISTER_PROPERTY(MeshColliderComponent, MaterialAssetHandle, AssetHandle, true, false);
    }
}
