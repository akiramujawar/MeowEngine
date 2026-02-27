//
// Created by Akira Mujawar on 22/02/26.
//

#include "FileSystem.hpp"

#include "filesystem"

namespace MeowEngine::Core::IO::FileSystem {


    bool FileSystem::Exists(const Path& path) {
        return filesystem::exists(path.GetRawString());
    }

    bool FileSystem::CreateDirectory(const Path& path) {
        return filesystem::create_directory(path.GetRawString());
    }

    bool FileSystem::Remove(const Path& path) {
        return filesystem::remove(path.GetRawString());
    }

    std::unique_ptr<File> FileSystem::Open(const Path& path, FileMode mode) {
        return std::unique_ptr<File>();
    }

    size_t FileSystem::FileSize(const Path& path) {
        return 0;
    }

    void FileSystem::Mount() {

    }

    void FileSystem::Unmount() {

    }

    void FileSystem::Resolve(const Path& virtualPath) {

    }


} // MeowEngine