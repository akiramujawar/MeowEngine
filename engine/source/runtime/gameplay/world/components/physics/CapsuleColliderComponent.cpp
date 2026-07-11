//
// Created by Akira Mujawar on 06/07/26.
//

#include "CapsuleColliderComponent.hpp"

namespace MeowEngine::Runtime {
    using Asset::AssetHandle;

    void CapsuleColliderComponent::Reflect() {
        REGISTER_PROPERTY(CapsuleColliderComponent, MaterialAssetHandle, AssetHandle, true, false);
        REGISTER_PROPERTY(CapsuleColliderComponent, Radius, float, true, true);
        REGISTER_PROPERTY(CapsuleColliderComponent, Height, float, true, true);
    }
}
