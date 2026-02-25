//
// Created by Akira Mujawar on 24/02/26.
//

#include "Directory.hpp"
#include "FileSystem.hpp"

namespace MeowEngine::Core::IO::FileSystem {

    Directory::Directory(const Path& pPath) : CurrentPath(pPath) {

    }

    bool Directory::Exists() const {
        return FileSystem::Exists(CurrentPath);
    }

    bool Directory::Create() {
        return FileSystem::CreateDirectory(CurrentPath);
    }

    bool Directory::Remove() {
        return FileSystem::Remove(CurrentPath);
    }

    std::vector<Path> Directory::GetFiles(bool pIncludeSubDirectories) const {
        return std::vector<Path>();
    }

    std::vector<Path> Directory::GetDirectories(bool pIncludeSubDirectories) const {
        return std::vector<Path>();
    }

    const Path& Directory::GetPath() const {
        return CurrentPath;
    }
}
