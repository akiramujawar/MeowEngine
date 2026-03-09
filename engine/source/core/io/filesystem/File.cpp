//
// Created by Akira Mujawar on 22/02/26.
//

#include "File.hpp"

#include <FileMode.hpp>
#include <Path.hpp>
#include <FileStream.hpp>


namespace MeowEngine::Core::IO::FileSystem {
    std::vector<u_int8_t> File::ReadAll(const std::string& path) {
        // std::ifstream file("project/source/kitty.png", std::ios::binary);
        //
        // std::vector<uint8_t> assetData(
        //     (std::istreambuf_iterator<char>(file)),
        //     std::istreambuf_iterator<char>()
        // );
        //
        // return assetData;

        FileStream stream;
        std::vector<u_int8_t> data;

        stream.Open(Path(path), FileMode::READ);
        stream.Read(data.data(), data.size());
        stream.Close();

        return data;
    }

    std::string File::ReadText(const std::string& path) {
        FileStream stream;
        std::string data;

        stream.Open(Path(path), FileMode::READ);
        stream.Read(data.data(), data.size());
        stream.Close();

        return data;
    }

    size_t File::Read(const std::string& path, void* buffer, size_t size) {
        FileStream stream;

        stream.Open(Path(path), FileMode::READ);
        stream.Read(buffer, size);
        stream.Close();

        return size;
    }

    size_t File::Write(const std::string& path, const void* buffer, size_t size) {
        FileStream stream;

        stream.Open(Path(path), FileMode::WRITE);
        stream.Write(buffer, size);
        stream.Flush();
        stream.Close();

        return size;
    }

}
