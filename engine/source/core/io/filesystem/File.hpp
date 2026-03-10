//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_FILE_HPP
#define MEOWENGINE_FILE_HPP

#include <cstdio>
#include <vector>

namespace MeowEngine::Core::IO::FileSystem {
    class Path;
    class FileStream;
    enum class FileMode;

    class File {
    public:
        static std::vector<u_int8_t> ReadAll(const std::string_view path);
        static std::string ReadText(const std::string_view path);

        static size_t Read(const std::string_view path, void* buffer, size_t size);
        static size_t Write(const std::string_view path, const void* buffer, size_t size);
    };

}


#endif //MEOWENGINE_FILE_HPP
