//
// Created by Akira Mujawar on 03/07/24.
//

#ifndef MEOWENGINE_TRANSFORM2D_COMPONENT_HPP
#define MEOWENGINE_TRANSFORM2D_COMPONENT_HPP

#include "IComponent.hpp"

namespace MeowEngine::Runtime {
    class Transform2DComponent : public IComponent {
    public:
        REFLECT_COMPONENT(Transform2DComponent)
        static void Reflect();
    };
}



#endif //MEOWENGINE_TRANSFORM2D_COMPONENT_HPP
