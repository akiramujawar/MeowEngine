//
// Created by Akira Mujawar on 19/02/26.
//

#include "selection_data.hpp"
#include "IO.hpp"
#include <Core.hpp>

namespace MeowEngine {
    SelectionData::SelectionData() {
        FileSystem::Path projectPath(GetProject().ProjectSettings.GetProjectPath());
        auto assetPath = projectPath + "source";
        
        SelectedDirectoryPath = assetPath.GetRawString();
    }
}