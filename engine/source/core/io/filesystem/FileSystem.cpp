//
// Created by Akira Mujawar on 22/02/26.
//

#include "FileSystem.hpp"

#include "filesystem"

namespace MeowEngine::Core::IO::FileSystem {


    bool FileSystem::Exists(const Path& pPath) {
        return filesystem::exists(pPath.CStr());
    }

    bool FileSystem::CreateDirectory(const Path& pPath) {
        return false;
    }

    bool FileSystem::Remove(const Path&) {
        return false;
    }

    std::unique_ptr<File> FileSystem::Open(const Path& pPath, FileMode pMode) {
        return std::unique_ptr<File>();
    }

    size_t FileSystem::FileSize(const Path& pPath) {
        return 0;
    }

    void FileSystem::Mount() {

    }

    void FileSystem::Unmount() {

    }

    void FileSystem::Resolve(const Path& pVirtualPath) {

    }


} // MeowEngine