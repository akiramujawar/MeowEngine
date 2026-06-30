//
// Created by Akira Mujawar on 20/06/26.
//

#ifndef MEOWENGINE_ENTITYREGISTRY_HPP
#define MEOWENGINE_ENTITYREGISTRY_HPP

#include "entt.hpp"
#include "Entity.hpp"
#include "EntityComponent.hpp"
#include "EntityHandle.hpp"

namespace MeowEngine::Runtime {
    using EntityRegistry = entt::basic_registry<Entity>;
}

#endif //MEOWENGINE_ENTITYREGISTRY_HPP