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

    Path::Path(const std::string& path) {
        CurrentPath = path;
    }

    Path::Path(const Types::String& path) {
        CurrentPath = path;
    }

    const char* Path::CStr() const {
        return CurrentPath.c_str();
    }

    const std::string& Path::GetRawString() const {
        return CurrentPath;
    }

    Types::String Path::GetString() const {
        return Types::String(CurrentPath);
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
        return FileSystem::Exists(CurrentPath);
    }

    Path Path::GetParent() const {
        filesystem::path currentPath { CurrentPath };

        auto end = currentPath.end();
        for(int i = 0; end != currentPath.begin() && i < 2; i++) {
            --end;
        }

        return { end->string() };
    }

    Path Path::GetName() const {
        filesystem::path currentPath { CurrentPath };

        return { currentPath.filename() };
    }

    Path Path::GetExtension() const {
        filesystem::path currentPath { CurrentPath };

        return { currentPath.filename() };
    }

    Path Path::ReplaceExtension(const std::string& extension) const {
        filesystem::path currentPath { CurrentPath };
        currentPath.replace_extension(extension);

        return { currentPath };
    }

    Path Path::ReplaceExtension(const Types::String& extension) const {
        filesystem::path currentPath { CurrentPath };
        currentPath.replace_extension(extension.c_str());

        return { currentPath.filename() };
    }

}