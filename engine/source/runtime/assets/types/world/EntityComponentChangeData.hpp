//
// Created by Akira Mujawar on 30/06/26.
//

#ifndef MEOWENGINE_ENTITYCOMPONENTCHANGEDATA_HPP
#define MEOWENGINE_ENTITYCOMPONENTCHANGEDATA_HPP

#include <typeindex>

#include "EntityHandle.hpp"
#include "EntityComponentChangeType.hpp"
#include "EntityComponent.hpp"

namespace MeowEngine::Asset {
    struct EntityComponentChangeData {
        Runtime::EntityHandle const& Handle;
        EntityComponentChangeType ChangeType;
        Runtime::EntityComponent const& ComponentType;
        // std::type_info const& ComponentType;
        // std::type_index const& ComponentTypeIndex;

        // entity handle
        // component type
        // component added / removed / enabled / disabled
    };
}

#endif //MEOWENGINE_ENTITYCOMPONENTCHANGEDATA_HPP