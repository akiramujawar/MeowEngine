//
// Created by Akira Mujawar on 26/01/26.
//

#ifndef MEOWENGINE_PERSPECTIVE_CAMERA_COMPONENT_HPP
#define MEOWENGINE_PERSPECTIVE_CAMERA_COMPONENT_HPP

#include "IComponent.hpp"

namespace MeowEngine::Runtime {
    class PerspectiveCameraComponent : public IComponent {
    public:
        REFLECT_COMPONENT(PerspectiveCameraComponent)
        static void Reflect();

        PerspectiveCameraComponent();
    };
}


#endif //MEOWENGINE_PERSPECTIVE_CAMERA_COMPONENT_HPP
