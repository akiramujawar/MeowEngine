//
// Created by Akira Mujawar on 19/02/26.
//

#ifndef MEOWENGINE_SELECTION_DATA_HPP
#define MEOWENGINE_SELECTION_DATA_HPP

#include "entt.hpp"
#include <Public/IO.hpp>

namespace MeowEngine {
    struct Selector {
        Selector();

        void Init(const Core::IO::FileSystem::Path& path);
        
        entt::entity SelectedEntity;
        std::string SelectedDirectoryPath;
        std::string SelectedAssetPath;
    };
}

#endif //MEOWENGINE_SELECTION_DATA_HPP
