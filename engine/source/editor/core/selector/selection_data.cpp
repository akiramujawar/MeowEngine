//
// Created by Akira Mujawar on 19/02/26.
//

#include "selection_data.hpp"
#include "IO.hpp"
#include "ProjectConfig.hpp"

namespace MeowEngine {
    SelectionData::SelectionData() {
        auto projectPath = FileSystem::Path(Settings::ProjectSettings::GetProjectPath());
        auto assetPath = projectPath + "source";
        
        SelectedDirectoryPath = assetPath.GetRawString();
    }
}