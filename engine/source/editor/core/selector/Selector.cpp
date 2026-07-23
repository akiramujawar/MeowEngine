//
// Created by Akira Mujawar on 19/02/26.
//

#include <Selector.hpp>

#include <Public/IO/Include.hpp>

namespace MeowEngine::Editor {
    Selector::Selector() : SelectedEntity() {}

    void Selector::Init(const FileSystem::Path& path) {
        const auto directoryPath = path + "assets";

        SelectedDirectoryPath = directoryPath.GetRawString();
    }
}
