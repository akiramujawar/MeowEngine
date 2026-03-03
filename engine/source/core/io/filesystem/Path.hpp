//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_PATH_HPP
#define MEOWENGINE_PATH_HPP

#include "String.hpp"

namespace MeowEngine::Core::IO::FileSystem {

    class Path {
    public:
//        Path();
        Path(const char* path);
        Path(const std::string_view& path);
//        Path(const Types::String& path);

        const char* CStr() const;
        const std::string_view& GetStringView() const;
        const std::string& GetRawString() const;
        const Types::String& GetString() const;
        
        Path operator+ (const char* path) const;
        Path operator+ (const std::string_view& path) const;
        Path operator+ (const Path& path) const;

        /**
         * Full path of file/folder
         * e.g. User://c/folder/folder
         * @return
         */
        bool IsAbsolute() const;

        /**
         * Relative to current directory
         * e.g. project/folder/folder
         * @return
         */
        bool IsRelative() const;
        bool Exists() const;

        Path GetParent() const;
        Path GetName() const;
        Path GetExtension() const;

        Path ReplaceExtension(const std::string& extension) const;
        Path ReplaceExtension(const Types::String& extension) const;

    private:
        std::string CurrentPath;

    };

}


#endif //MEOWENGINE_PATH_HPP
