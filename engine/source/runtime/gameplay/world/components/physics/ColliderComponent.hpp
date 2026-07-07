//
// Created by Akira Mujawar on 07/07/26.
//

#ifndef MEOWENGINE_COLLIDERCOMPONENT_HPP
#define MEOWENGINE_COLLIDERCOMPONENT_HPP

#include "IComponent.hpp"
#include "AssetHandle.hpp"

namespace MeowEngine::Runtime {
    /**
     * This class is extended for mesh, debug & ui rendering
     */
    class ColliderComponent : public IComponent {
    protected:
        ColliderComponent() = default;
        ~ColliderComponent() override = default;

    public:
        [[nodiscard]] Asset::AssetHandle GetMaterialAssetHandle() const { return MaterialAssetHandle; }

    protected:
        Asset::AssetHandle MaterialAssetHandle;
    };
}

#endif //MEOWENGINE_COLLIDERCOMPONENT_HPP