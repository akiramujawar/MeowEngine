//
// Created by Akira Mujawar on 04/07/26.
//

#ifndef MEOWENGINE_HIERARCHY_HPP
#define MEOWENGINE_HIERARCHY_HPP

#include "EntityHandle.hpp"

namespace MeowEngine::Asset {
    class World;
}

namespace MeowEngine::Runtime {
    // hierarchy later can actually store the actual hierarchy
    // extractor can extract root entities from here instead of registry
    // serializer can also store this
    // rename that time to HierarchyManager
    class Hierarchy {

    public:
        /**
         * Reset parent & other childs
         * @param world
         * @param handle
         */
        static void DetachParent(Asset::World& world, const EntityHandle& handle);

        /**
         *
         * @param world
         * @param child
         * @param parent
         */
        static void AttachParent(Asset::World& world, const EntityHandle& child , const EntityHandle& parent);

        /**
         * Invalidate moved entity hierarchy
         * @param world
         * @param handle
         */
        static void Reset(Asset::World& world, const EntityHandle& handle);

    };
}


#endif //MEOWENGINE_HIERARCHY_HPP