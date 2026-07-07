//
// Created by Akira Mujawar on 06/07/26.
//

#ifndef MEOWENGINE_MESHCOLLIDERCOMPONENT_HPP
#define MEOWENGINE_MESHCOLLIDERCOMPONENT_HPP

#include <ColliderComponent.hpp>

namespace MeowEngine::Runtime {
    class MeshColliderComponent : public ColliderComponent {
    public:
        REFLECT_COMPONENT(MeshColliderComponent)
        static void Reflect();

        MeshColliderComponent() = default;
        ~MeshColliderComponent() override = default;
    };
}



#endif //MEOWENGINE_MESHCOLLIDERCOMPONENT_HPP