//
// Created by Akira Mujawar on 06/07/26.
//

#ifndef MEOWENGINE_SPHERECOLLIDERCOMPONENT_HPP
#define MEOWENGINE_SPHERECOLLIDERCOMPONENT_HPP

#include <ColliderComponent.hpp>

namespace MeowEngine::Runtime {
    class SphereColliderComponent : public ColliderComponent {
    public:
        REFLECT_COMPONENT(SphereColliderComponent)
        static void Reflect();

        SphereColliderComponent() = default;
        ~SphereColliderComponent() override = default;

        float Radius;
    };
}



#endif //MEOWENGINE_SPHERECOLLIDERCOMPONENT_HPP