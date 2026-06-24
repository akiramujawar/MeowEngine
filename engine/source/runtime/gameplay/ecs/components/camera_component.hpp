//
// Created by Akira Mujawar on 26/01/26.
//

#ifndef MEOWENGINE_CAMERA_COMPONENT_HPP
#define MEOWENGINE_CAMERA_COMPONENT_HPP

#include "ComponentBase.hpp"

namespace MeowEngine::Runtime {
    struct CameraComponent : public MeowEngine::Runtime::ComponentBase {
    public:
        REFLECT_COMPONENT(CameraComponent)
        static void Reflect();

        CameraComponent();
    };
}


#endif //MEOWENGINE_CAMERA_COMPONENT_HPP
