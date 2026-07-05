//
// Created by Akira Mujawar on 19/02/26.
//

#ifndef MEOWENGINE_GRID_COMPONENT_HPP
#define MEOWENGINE_GRID_COMPONENT_HPP

#include "RenderComponent.hpp"

namespace MeowEngine::Runtime {
    class GridComponent : public RenderComponent {
    public:
        REFLECT_COMPONENT(GridComponent)
        static void Reflect();

        explicit GridComponent();
        ~GridComponent() override = default;
    };
}

#endif //MEOWENGINE_GRID_COMPONENT_HPP
