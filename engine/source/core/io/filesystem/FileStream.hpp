//
// Created by Akira Mujawar on 24/02/26.
//

#ifndef MEOWENGINE_FILESTREAM_HPP
#define MEOWENGINE_FILESTREAM_HPP

#include <cstdio>
#include <fstream>

namespace MeowEngine::Core::IO::FileSystem {
    class Path;
    enum class FileMode;

    class FileStream {
    public:
        ~FileStream();

        bool Open(const Path& path, FileMode mode);
        void Close();

        std::size_t Read(void* buffer, std::size_t size);
        std::size_t Write(const void* buffer, std::size_t size);

        void Seek(std::size_t position);

        std::size_t Size();

        /**
         * Returns current position
         */
        std::size_t Tell();

        /**
         * Save data to the disk
         */
        void Flush();

        bool IsOpen() const;

    private:
        std::fstream Stream; // input + output operations
    };

}


#endif //MEOWENGINE_FILESTREAM_HPP
