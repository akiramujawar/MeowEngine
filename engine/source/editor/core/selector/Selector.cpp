//
// Created by Akira Mujawar on 19/02/26.
//

#include "Selector.hpp"

#include <Public/IO.hpp>

namespace MeowEngine {
    Selector::Selector() {
        // FileSystem::Path projectPath(GetProject().ProjectSettings.GetProjectPath());
        // auto assetPath = projectPath + "source";
        //
        // SelectedDirectoryPath = assetPath.GetRawString();
    }

    void Selector::Init(const FileSystem::Path& path) {
        const auto assetPath = path + "source";

        SelectedDirectoryPath = assetPath.GetRawString();
    }
}
