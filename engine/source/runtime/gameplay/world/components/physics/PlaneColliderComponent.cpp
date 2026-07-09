//
// Created by Akira Mujawar on 03/07/26.
//

#include "PlaneColliderComponent.hpp"

namespace MeowEngine::Runtime {
    using Asset::AssetHandle;

    void PlaneColliderComponent::Reflect() {
        REGISTER_PROPERTY(PlaneColliderComponent, MaterialAssetHandle, AssetHandle, true, false);
    }
}
