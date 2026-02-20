//
// Created by Akira Mujawar on 01/08/24.
//

#ifndef MEOWENGINE_INFO_COMPONENT_HPP
#define MEOWENGINE_INFO_COMPONENT_HPP

#include "pstring.hpp"
#include "component_base.hpp"

namespace MeowEngine::entity {
    struct InfoComponent : public MeowEngine::entity::ComponentBase {
    public:
        REFLECT_COMPONENT(InfoComponent)
        static void Reflect();

        InfoComponent(std::string name);

        MeowEngine::PString Name;
    };
}


#endif //MEOWENGINE_INFO_COMPONENT_HPP
