//
// Created by Akira Mujawar on 19/02/26.
//

#ifndef MEOWENGINE_SELECTION_DATA_HPP
#define MEOWENGINE_SELECTION_DATA_HPP

#include <Public/IO/Forward.hpp>
#include <entt.hpp>

namespace MeowEngine::Editor {
    struct Selector {
        Selector();

        void Init(const FileSystem::Path& path);
        
        entt::entity SelectedEntity;
        std::vector<entt::entity> SelectedEntities;

        std::string SelectedDirectoryPath;
        std::string SelectedAssetPath;
    };
}

#endif //MEOWENGINE_SELECTION_DATA_HPP
