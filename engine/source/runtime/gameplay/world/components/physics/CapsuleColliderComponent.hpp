//
// Created by Akira Mujawar on 06/07/26.
//

#ifndef MEOWENGINE_CAPSULECOLLIDERCOMPONENT_HPP
#define MEOWENGINE_CAPSULECOLLIDERCOMPONENT_HPP

#include <ColliderComponent.hpp>

namespace MeowEngine::Runtime {
    class CapsuleColliderComponent : public ColliderComponent {
    public:
        REFLECT_COMPONENT(CapsuleColliderComponent)
        static void Reflect();

        CapsuleColliderComponent() = default;
        ~CapsuleColliderComponent() override = default;
    };
}



#endif //MEOWENGINE_CAPSULECOLLIDERCOMPONENT_HPP