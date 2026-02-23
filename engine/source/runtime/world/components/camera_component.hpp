//
// Created by Akira Mujawar on 26/01/26.
//

#ifndef MEOWENGINE_CAMERA_COMPONENT_HPP
#define MEOWENGINE_CAMERA_COMPONENT_HPP

#include "component_base.hpp"

namespace MeowEngine::entity {
    struct CameraComponent : public MeowEngine::entity::ComponentBase {
    public:
        REFLECT_COMPONENT(CameraComponent)
        static void Reflect();

        CameraComponent();
    };
}


#endif //MEOWENGINE_CAMERA_COMPONENT_HPP
