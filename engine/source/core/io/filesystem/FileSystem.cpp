//
// Created by Akira Mujawar on 22/02/26.
//

#include "FileSystem.hpp"

#include "filesystem"

#if (__WEB__)

#elif __APPLE__
    #include <mach-o/dyld.h>
#elif __linux__

#elif _WIN32

#endif


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

    Path FileSystem::GetExecutablePath() {
        #if (__WEB__)
            auto executableDir = std::filesystem::current_path();
        #elif __APPLE__
            uint32_t size = 0;
            _NSGetExecutablePath(nullptr, &size);

            std::string buffer(size, '\0');
            _NSGetExecutablePath(buffer.data(), &size);

            auto executableDir = std::filesystem::canonical(buffer).parent_path();
        #elif __linux__
            auto exeDir = std::filesystem::canonical("/proc/self/exe");
        #elif _WIN32
            // char path[MAX_PATH];
            // GetModuleFileNameA(nullptr, path, MAX_PATH);
            // auto executableDir = std::filesystem::path(path)
        #endif

        return {executableDir.c_str()};
    }

    bool FileSystem::Move(const Path& filePath , const Path& directoryToMovePath) {
        if(!IsDirectory(directoryToMovePath)) {
            MeowEngine::Log("FileSystem::Move", {directoryToMovePath.GetRawString(), "Not a directory"})  ;
        }
        
        std::error_code errorCode;
        
        const Path& newPath(directoryToMovePath + filePath.GetName());
        
        filesystem::rename(filePath.GetRawString(), newPath.GetRawString(), errorCode);
        
        
        if(errorCode) {
            MeowEngine::Log("Move", {filePath.GetRawString(), newPath.GetRawString(), errorCode.message()}, LogType::ERROR);
            
            return false;
        }
        
        return true;
    }

    bool FileSystem::Replace(const Path& a, const Path& b) {
        Remove(a);

        std::error_code errorCode;
        filesystem::rename(b.GetRawString(), a.GetRawString(), errorCode);

        if(errorCode) {
            MeowEngine::Log("Move", {a.GetRawString(), b.GetRawString(), errorCode.message()}, LogType::ERROR);

            return false;
        }

        return true;
    }

    bool FileSystem::Rename(const Path& path, const std::string_view & name) {
        std::error_code errorCode;
        
        const Path& directoryPath = path.GetParent();
        const Path& extension = path.GetExtension();
        Path newPath = directoryPath + name;
        newPath.ReplaceExtension(extension.GetRawString());
        
        filesystem::rename(path.GetRawString(), newPath.GetRawString(), errorCode);
        
        if(errorCode) {
            MeowEngine::Log("Rename", {path.GetRawString(), newPath.GetRawString(), errorCode.message()}, LogType::ERROR);
            
            return false;
        }
        
        return true;
    }

    bool FileSystem::Remove(const Path& path) {
        std::error_code errorCode;
        filesystem::remove(path.GetRawString(), errorCode);
   
        if(errorCode) {
            MeowEngine::Log("Rename", {path.GetRawString(), errorCode.message()}, LogType::ERROR);
        
            return false;
        }
    
        return true;
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