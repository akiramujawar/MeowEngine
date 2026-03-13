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

        [[nodiscard]] const char* CStr() const;
        [[nodiscard]] std::string_view GetStringView() const;
        [[nodiscard]] const std::string& GetRawString() const;
        [[nodiscard]] const Types::String& GetString() const;
        
        Path operator+ (const char* path) const;
        Path operator+ (const std::string_view& path) const;
        Path operator+ (const Path& path) const;

        Path operator+= (const char* path) const;
        Path operator+= (const std::string_view& path) const;
        Path operator+= (const Path& path) const;

        /**
         * Full path of file/folder
         * e.g. User://c/folder/folder
         * @return
         */
        [[nodiscard]] bool IsAbsolute() const;

        /**
         * Relative to current directory
         * e.g. project/folder/folder
         * @return
         */
        [[nodiscard]] bool IsRelative() const;
        [[nodiscard]] bool Exists() const;

        [[nodiscard]] Path GetParent() const;
        [[nodiscard]] Path GetName() const;
        [[nodiscard]] Path GetExtension() const;

        void ReplaceName(const std::string& name);
        void ReplaceExtension(const std::string& extension);
        void ReplaceExtension(const Types::String& extension);

    private:
        std::string CurrentPath;

    };

}


#endif //MEOWENGINE_PATH_HPP
