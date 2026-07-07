//
// Created by Akira Mujawar on 03/07/26.
//

#ifndef MEOWENGINE_PLANECOLLIDERCOMPONENT_HPP
#define MEOWENGINE_PLANECOLLIDERCOMPONENT_HPP

#include <ColliderComponent.hpp>

namespace MeowEngine::Runtime {
    class PlaneColliderComponent : public ColliderComponent {
    public:
        REFLECT_COMPONENT(PlaneColliderComponent)
        static void Reflect();

        PlaneColliderComponent() = default;
        ~PlaneColliderComponent() override = default;
    };
}


#endif //MEOWENGINE_PLANECOLLIDERCOMPONENT_HPP