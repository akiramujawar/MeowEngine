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
    };
}

#endif //MEOWENGINE_RENDERUIDATA_HPP