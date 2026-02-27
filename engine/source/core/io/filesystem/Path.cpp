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

    Path Path::operator+ (const Path& path) {
        filesystem::path currentPath(CurrentPath);
        filesystem::path newPath = currentPath / path.CurrentPath;

        return Path { newPath.string() };
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

        auto end = currentPath.end();
        for(int i = 0; end != currentPath.begin() && i < 2; i++) {
            --end;
        }

        return Path { end->string() };
    }

    Path Path::GetName() const {
        filesystem::path currentPath { CurrentPath };

        return Path { currentPath.filename().string() };
    }

    Path Path::GetExtension() const {
        filesystem::path currentPath { CurrentPath };

        return Path { currentPath.extension().string() };
    }

    Path Path::ReplaceExtension(const std::string& extension) const {
        filesystem::path currentPath { CurrentPath };
        currentPath.replace_extension(extension);

        return Path { currentPath.string() };
    }

    Path Path::ReplaceExtension(const Types::String& extension) const {
        filesystem::path currentPath { CurrentPath };
        currentPath.replace_extension(extension.c_str());

        return Path { currentPath.filename().string() };
    }

}