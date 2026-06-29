//
// Created by Akira Mujawar on 03/07/24.
//

#ifndef MEOWENGINE_TRANSFORM3D_COMPONENT_HPP
#define MEOWENGINE_TRANSFORM3D_COMPONENT_HPP

#include "IComponent.hpp"
#include "Public/Math.hpp"

namespace MeowEngine::Runtime {
    class Transform3DComponent : public IComponent {
    public:
        REFLECT_COMPONENT(Transform3DComponent)
        static void Reflect();

    public:
        Transform Local;
    };
}


#endif //MEOWENGINE_TRANSFORM3D_COMPONENT_HPP
