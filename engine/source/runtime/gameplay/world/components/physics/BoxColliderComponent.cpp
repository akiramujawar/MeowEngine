//
// Created by Akira Mujawar on 06/07/26.
//

#include "BoxColliderComponent.hpp"


namespace MeowEngine::Runtime {
    using Asset::AssetHandle;

    void BoxColliderComponent::Reflect() {
        REGISTER_PROPERTY(BoxColliderComponent, MaterialAssetHandle, AssetHandle, true, false);
    }
}
