//
// Created by Akira Mujawar on 23/06/24.
//

#ifndef MEOWENGINE_SKY_BOX_COMPONENT_BASE_HPP
#define MEOWENGINE_SKY_BOX_COMPONENT_BASE_HPP

#include "RenderComponent.hpp"
#include "AssetHandle.hpp"

namespace MeowEngine::Runtime {
    class SkyBoxComponent : public RenderComponent {

    public:
        REFLECT_COMPONENT(SkyBoxComponent)
        static void Reflect();

        explicit SkyBoxComponent();
        ~SkyBoxComponent() override = default;
    };
}

#endif //MEOWENGINE_SKY_BOX_COMPONENT_BASE_HPP
