//
// Created by Akira Mujawar on 23/06/24.
//

#ifndef MEOWENGINE_COMPONENT_BASE_HPP
#define MEOWENGINE_COMPONENT_BASE_HPP

#include "m_object.hpp"

namespace MeowEngine::entity {
    class ComponentBase : MObject{
        std::string GetClassName() override {
            return "ComponentBase";
        };
        // component method's like init & update - virtual
    };
}


#endif //MEOWENGINE_COMPONENT_BASE_HPP
