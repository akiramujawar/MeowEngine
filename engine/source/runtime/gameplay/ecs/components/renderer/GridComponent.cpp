//
// Created by Akira Mujawar on 19/02/26.
//

#include "GridComponent.hpp"

namespace MeowEngine::Runtime {
    using Asset::AssetHandle;

    void GridComponent::Reflect() {
        REGISTER_PROPERTY(GridComponent, ShaderHandle, AssetHandle, true, false);
    }

    GridComponent::GridComponent() {}

}