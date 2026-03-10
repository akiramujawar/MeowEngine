//
// Created by Akira Mujawar on 22/02/26.
//

#include "File.hpp"

#include <FileMode.hpp>
#include <Path.hpp>
#include <FileStream.hpp>


namespace MeowEngine::Core::IO::FileSystem {
    std::vector<u_int8_t> File::ReadAll(const std::string_view path) {
        FileStream stream;
        stream.Open(Path(path), FileMode::READ);

        std::size_t size = stream.Size();
        std::vector<u_int8_t> data(size);

        stream.Read(data.data(), data.size());
        stream.Close();

        return data;
    }

    std::string File::ReadText(const std::string_view path) {
        FileStream stream;
        std::string data;

        stream.Open(Path(path), FileMode::READ);
        stream.Read(data.data(), data.size());
        stream.Close();

        return data;
    }

    size_t File::Read(const std::string_view path, void* buffer, size_t size) {
        FileStream stream;

        stream.Open(Path(path), FileMode::READ);
        stream.Read(buffer, size);
        stream.Close();

        return size;
    }

    size_t File::Write(const std::string_view path, const void* buffer, size_t size) {
        FileStream stream;

        stream.Open(Path(path), FileMode::WRITE);
        stream.Write(buffer, size);
        stream.Flush();
        stream.Close();

        return size;
    }

}
