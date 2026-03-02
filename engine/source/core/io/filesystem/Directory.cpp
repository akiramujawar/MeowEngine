//
// Created by Akira Mujawar on 24/02/26.
//

#include "Directory.hpp"
#include "FileSystem.hpp"
#include "Path.hpp"

namespace MeowEngine::Core::IO::FileSystem {

    Directory::Directory(const Path& path) : CurrentPath(path) {}
    
    bool Directory::Exists() const {
        return FileSystem::Exists(CurrentPath);
    }

    bool Directory::Create() {
        return FileSystem::CreateDirectory(CurrentPath);
    }

    bool Directory::Remove() {
        return FileSystem::Remove(CurrentPath);
    }

    std::vector<Path> Directory::GetFiles(bool includeSubDirectories) const {
        std::vector<Path> files;

        // if not a folder return empty
        if(!FileSystem::IsDirectory(CurrentPath)) {
            return files;
        }

        // collect only files
        for (auto entry: filesystem::directory_iterator{CurrentPath.GetRawString()}) {
            if(entry.is_regular_file()) {
                files.push_back(Path(entry.path().string()));
            }
        }

        return files;
    }

    std::vector<Path> Directory::GetDirectories(bool includeSubDirectories) const {
        std::vector<Path> files;

        // if not a folder return empty
        if(!FileSystem::IsDirectory(CurrentPath)) {
            return files;
        }

        // collect only folders
        for (auto entry: filesystem::directory_iterator{CurrentPath.CStr()}) {
            if(entry.is_directory()) {
                files.push_back(Path(entry.path().string()));
            }
        }

        return files;
    }

    std::vector<Path> Directory::GetAll(bool includeSubDirectories) const {
        std::vector<Path> files;

        // if not a folder return empty
        if(!FileSystem::IsDirectory(CurrentPath)) {
            return files;
        }

        // collect only folders
        for (auto entry: filesystem::directory_iterator{CurrentPath.CStr()}) {
            files.push_back(Path(entry.path().string()));
        }

        return files;
    }

    const Path& Directory::GetPath() const {
        return CurrentPath;
    }
}
