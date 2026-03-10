//
// Created by Akira Mujawar on 22/02/26.
//

#include "Path.hpp"
#include "FileSystem.hpp"
#include "filesystem"

namespace MeowEngine::Core::IO::FileSystem {

//    Path::Path() {
//
//    }

    Path::Path(const char* path) {
        CurrentPath = path;
    }

    Path::Path(const std::string_view& path) {
        CurrentPath = std::string(path);
    }

//    Path::Path(const Types::String& path) {
//        CurrentPath = path;
//    }

    const char* Path::CStr() const {
        return CurrentPath.c_str();
    }

    const std::string_view& Path::GetStringView() const {
        return CurrentPath;
    }

    const std::string& Path::GetRawString() const {
        return CurrentPath;
    }


    const Types::String& Path::GetString() const {
        return Types::String(CurrentPath);
    }
    
    Path Path::operator+ (const char* path) const {
        filesystem::path currentPath(CurrentPath);
        filesystem::path newPath = currentPath / path;
        
        return Path { newPath.string() };
    }
    
    Path Path::operator+ (const std::string_view& path) const {
        filesystem::path currentPath(CurrentPath);
        filesystem::path newPath = currentPath / path;
        
        return Path { newPath.string() };
    }
    
    Path Path::operator+ (const Path& path) const {
        filesystem::path currentPath(CurrentPath);
        filesystem::path newPath = currentPath / path.CurrentPath;

        return Path { newPath.string() };
    }

    Path Path::operator+=(const char* path) const {
        return {""};
    }

    Path Path::operator+=(const std::string_view& path) const {
        return {""};
    }

    Path Path::operator+=(const Path& path) const {
        return {""};
    }

    bool Path::IsAbsolute() const {
        filesystem::path currentPath { CurrentPath };
        return currentPath.is_absolute();
    }

    bool Path::IsRelative() const {
        filesystem::path currentPath { CurrentPath };
        return currentPath.is_relative();
    }

    bool Path::Exists() const {
        return FileSystem::Exists(Path {CurrentPath});
    }

    Path Path::GetParent() const {
        filesystem::path currentPath { CurrentPath };
        
        if(currentPath.has_parent_path()) {
            return Path(currentPath.parent_path().string());
        }
        else {
            return Path("");
        }
    }

    Path Path::GetName() const {
        filesystem::path currentPath { CurrentPath };

        return Path { currentPath.stem().string() };
    }

    Path Path::GetExtension() const {
        filesystem::path currentPath { CurrentPath };

        return Path { currentPath.extension().string() };
    }

    void Path::ReplaceExtension(const std::string& extension) {
        filesystem::path currentPath { CurrentPath };
        currentPath.replace_extension(extension);

        CurrentPath = currentPath.string();
        // return Path { currentPath.string() };
    }

    void Path::ReplaceExtension(const Types::String& extension) {
        filesystem::path currentPath { CurrentPath };
        currentPath.replace_extension(extension.c_str());

        CurrentPath = currentPath.string();
        // return Path { currentPath.filename().string() };
    }

}