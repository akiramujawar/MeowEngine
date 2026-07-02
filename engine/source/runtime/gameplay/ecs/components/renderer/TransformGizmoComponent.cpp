//
// Created by Akira Mujawar on 18/02/26.
//

#include "TransformGizmoComponent.hpp"

namespace MeowEngine::Runtime {
    using Asset::AssetHandle;

    void TransformGizmoComponent::Reflect() {
        REGISTER_PROPERTY(TransformGizmoComponent, ShaderAssetHandle, AssetHandle, true, false);
    }

    TransformGizmoComponent::TransformGizmoComponent() {}

}