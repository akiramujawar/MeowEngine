//
// Created by Akira Mujawar on 19/02/26.
//

#ifndef MEOWENGINE_SELECTION_DATA_HPP
#define MEOWENGINE_SELECTION_DATA_HPP

#include "entt.hpp"

namespace MeowEngine {
    struct SelectionData {
        entt::entity SelectedEntity;
        std::string SelectedDirectoryPath;
        std::string SelectedAssetPath;
    };
}

#endif //MEOWENGINE_SELECTION_DATA_HPP
