//
// Created by Akira Mujawar on 23/06/24.
//

#include "SkyBoxComponent.hpp"
#include <log.hpp>

namespace MeowEngine::Runtime {
    using Asset::AssetHandle;

    void MeowEngine::Runtime::SkyBoxComponent::Reflect() {
        REGISTER_PROPERTY(SkyBoxComponent, ShaderAssetHandle, AssetHandle, true, false);
    }

    SkyBoxComponent::SkyBoxComponent() {}

}
