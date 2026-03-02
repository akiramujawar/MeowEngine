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
        std::error_code errorCode;
        
        if(filesystem::create_directory(path.GetRawString(), errorCode)) {
            return true;
        }
        
        MeowEngine::Log("Create Directory", {path.GetRawString(), errorCode.message()}, LogType::ERROR);
        
        return false;
    }
    
    bool FileSystem::IsDirectory(const Path &path) {
        filesystem::directory_entry directoryEntry (path.GetRawString());
        
        return directoryEntry.is_directory();
    }
    
    bool FileSystem::Move(const Path& filePath , const Path& directoryToMovePath) {
        if(!IsDirectory(directoryToMovePath)) {
            MeowEngine::Log("FileSystem::Move", {directoryToMovePath.GetRawString(), "Not a directory"})  ;
        }
        
        std::error_code errorCode;
        
        filesystem::rename(filePath.GetRawString(), directoryToMovePath.GetRawString(), errorCode);
        
        if(errorCode) {
            MeowEngine::Log("Move", {filePath.GetRawString(), errorCode.message()}, LogType::ERROR);
            
            return false;
        }
        
        return true;
    }
    
    bool FileSystem::Rename(const Path& path, const std::string_view & name) {
        std::error_code errorCode;
        const Path& newPath = path + name;
        
        filesystem::rename(path.GetRawString(), newPath.GetRawString(), errorCode);
        
        if(errorCode) {
            MeowEngine::Log("Rename", {newPath.GetRawString(), errorCode.message()}, LogType::ERROR);
            
            return false;
        }
        
        return true;
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