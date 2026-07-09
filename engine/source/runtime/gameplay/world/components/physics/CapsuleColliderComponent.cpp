//
// Created by Akira Mujawar on 06/07/26.
//

#include "CapsuleColliderComponent.hpp"

namespace MeowEngine::Runtime {
    using Asset::AssetHandle;

    void CapsuleColliderComponent::Reflect() {
        REGISTER_PROPERTY(CapsuleColliderComponent, MaterialAssetHandle, AssetHandle, true, false);
    }
}
