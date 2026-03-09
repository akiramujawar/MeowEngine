//
// Created by Akira Mujawar on 24/02/26.
//

#include "FileStream.hpp"
#include <FileMode.hpp>
#include <Path.hpp>


namespace MeowEngine::Core::IO::FileSystem {
    FileStream::~FileStream() {}

    bool FileStream::Open(const Path& path, FileMode mode) {
        Close();

        std::ios::openmode openMode = std::ios::binary;

        // https://en.cppreference.com/w/cpp/io/ios_base/openmode.html
        switch (mode) {
            case FileMode::READ:
                openMode |= std::ios::in;
                break;
            case FileMode::WRITE:
                openMode |= std::ios::out | std::ios::trunc;
                break;
            case FileMode::APPEND:
                openMode |= std::ios::out | std::ios::app;
                break;
            case FileMode::READ_WRITE:
                openMode |= std::ios::in | std::ios::out;
                break;
        }

        Stream.open(path.GetRawString(), openMode);

        return Stream.is_open();
    }

    void FileStream::Close() {
        if (Stream.is_open()) {
            Stream.close();
        }
    }

    std::size_t FileStream::Read(void* buffer, std::size_t size) {
        if (!Stream.is_open()) {
            return 0;
        }

        Stream.read(static_cast<char*>(buffer), size);

        return Stream.gcount();
    }

    std::size_t FileStream::Write(const void* buffer, std::size_t size) {
        if (!Stream.is_open()) {
            return 0;
        }

        Stream.write(static_cast<const char*>(buffer), size);

        if (Stream.bad()) {
            return 0;
        }

        return size;
    }

    void FileStream::Seek(std::size_t position) {
        if (!Stream.is_open()) {
            return;
        }

        Stream.seekg(position, std::ios::beg);
        Stream.seekp(position, std::ios::beg);
    }

    std::size_t FileStream::Size() {
        if (!Stream.is_open()) {
            return 0;
        }

        // cache the current indicator
        auto currentIndicator = Tell();

        // calc size from begin to end by moving the indicator
        Stream.seekg(0, std::ios::end);
        const auto size = Stream.tellg();

        // revert the indicator to its previous cached state
        Seek(currentIndicator);

        return size;
    }

    std::size_t FileStream::Tell() {
        if (!Stream.is_open()) {
            return 0;
        }

        auto indicator = Stream.tellg(); // input indicator
        if (indicator == -1) {
            indicator = Stream.tellp(); // output indicator
        }

        return indicator;
    }

    void FileStream::Flush() {
        if (Stream.is_open()) {
            Stream.flush();
        }
    }

    bool FileStream::IsOpen() const {
        return Stream.is_open();
    }
}
