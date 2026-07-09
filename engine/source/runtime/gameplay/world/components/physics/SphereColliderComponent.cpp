//
// Created by Akira Mujawar on 06/07/26.
//

#include "SphereColliderComponent.hpp"

namespace MeowEngine::Runtime {
    using Asset::AssetHandle;

    void SphereColliderComponent::Reflect() {
        REGISTER_PROPERTY(SphereColliderComponent, MaterialAssetHandle, AssetHandle, true, false);
    }
}
