//
// Created by Akira Mujawar on 09/06/26.
//

#ifndef MEOWENGINE_RENDERUIDATA_HPP
#define MEOWENGINE_RENDERUIDATA_HPP

#include <Public/Core.hpp>

namespace MeowEngine::Rendering {
    /**
     * Data used for drawing entities in Tree Panel
     */
    struct RenderEntityHierarchy {
        uint32_t GUID;
        String Name;

        std::vector<uint32_t> Childs;
    };

    struct RenderEntityComponent {
        entt::id_type Type;
        std::string Name;
        void* DataObject; // TODO: as rework in future try replacing void* with Engine Object
    };

    struct RenderUIData {
        /**
         * We track only the roots for tree panel and
         * then recursively expand the childs using @EntityHierarchyMap
         */
        std::vector<uint32_t> RootEntities;

        /**
         * All entities to be listed in tree panel
         */
        std::unordered_map<uint32_t, RenderEntityHierarchy> EntityHierarchyMap;

        /**
         * All the selected entities (are same for scene & ui (tree panel))
         */
        std::unordered_set<uint32_t> SelectedEntities;

        /**
         * A reflected clone of components attached to last selected entity
         */
        std::vector<RenderEntityComponent> LastSelectedEntityComponents;
    };
}

#endif //MEOWENGINE_RENDERUIDATA_HPP