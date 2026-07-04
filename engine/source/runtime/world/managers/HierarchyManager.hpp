//
// Created by Akira Mujawar on 04/07/26.
//

#ifndef MEOWENGINE_HIERARCHYMANAGER_HPP
#define MEOWENGINE_HIERARCHYMANAGER_HPP

#include "EntityHandle.hpp"

namespace MeowEngine::Asset {
    class World;
}

namespace MeowEngine::Runtime {
    class HierarchyManager {

    public:
        /**
         * Reset parent & other childs
         * @param world
         * @param handle
         */
        void DetachParent(Asset::World& world, const EntityHandle& handle);

        /**
         *
         * @param world
         * @param child
         * @param parent
         */
        void AttachParent(Asset::World& world, const EntityHandle& child , const EntityHandle& parent);

        /**
         * Invalidate moved entity hierarchy
         * @param world
         * @param handle
         */
        void Reset(Asset::World& world, const EntityHandle& handle);
    };
}


#endif //MEOWENGINE_HIERARCHYMANAGER_HPP