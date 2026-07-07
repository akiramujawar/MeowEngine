//
// Created by Akira Mujawar on 06/07/26.
//

#ifndef MEOWENGINE_BOXCOLLIDERCOMPONENT_HPP
#define MEOWENGINE_BOXCOLLIDERCOMPONENT_HPP


#include <ColliderComponent.hpp>

namespace MeowEngine::Runtime {
    class BoxColliderComponent : public ColliderComponent {
    public:
        REFLECT_COMPONENT(BoxColliderComponent)
        static void Reflect();

        BoxColliderComponent() = default;
        ~BoxColliderComponent() override = default;
    };
}


#endif //MEOWENGINE_BOXCOLLIDERCOMPONENT_HPP