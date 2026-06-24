//
// Created by Akira Mujawar on 09/06/26.
//

#ifndef MEOWENGINE_RENDERUIDATA_HPP
#define MEOWENGINE_RENDERUIDATA_HPP

#include <Public/Core/Include.hpp>
#include "EntityHandle.hpp"
#include "FolderCache.hpp"
#include "AssetDirectory.hpp"

namespace MeowEngine::Rendering {
    /**
     * Data used for drawing entities in Tree Panel
     */
    struct RenderEntityHierarchy {
        Runtime::EntityHandle Handle;
        String Name;

        std::vector<Runtime::EntityHandle> Childs;
    };

    struct RenderEntityComponent {
        Runtime::ComponentID Type;
        std::string Name;
        void* DataObject; // TODO: as rework in future try replacing void* with Engine Object
    };

    struct RenderUIData {
        RenderUIData() : SelectedFolderPath(""), SelectedFilePath("") {
            LastSelectedEntity = Runtime::EntityHandle::Invalid();
        }

        /**
         * We track only the roots for tree panel and
         * then recursively expand the childs using @EntityHierarchyMap
         */
        std::vector<Runtime::EntityHandle> RootEntities;

        /**
         * All entities to be listed in tree panel
         */
        std::unordered_map<Runtime::EntityHandle, RenderEntityHierarchy> EntityHierarchyMap;

        /**
         * All the selected entities (are same for scene & ui (tree panel))
         */
        std::unordered_set<Runtime::EntityHandle> SelectedEntities;

        /**
         * Latest selected entity
         */
        Runtime::EntityHandle LastSelectedEntity;

        /**
         * A reflected clone of components attached to last selected entity
         */
        std::vector<RenderEntityComponent> LastSelectedEntityComponents;

        // NOTE: create a StringHash / StringView which will contain guid. Then we can use to compare guid's
        // think it through as it can optimise lot more even for assigning string values.
        Path SelectedFolderPath;
        Path SelectedFilePath;

        std::vector<Asset::DirectoryAsset> FilesInSelectedFolder;
        Asset::FolderCache EngineDirectoryMap;
        Asset::FolderCache SandboxDirectoryMap;
    };
}

#endif //MEOWENGINE_RENDERUIDATA_HPP