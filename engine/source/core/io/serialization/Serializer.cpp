//
// Created by Akira Mujawar on 11/03/26.
//

#include "Serializer.hpp"

#include <FileStream.hpp>
#include <utility>

#include "Path.hpp"

namespace MeowEngine::Core::IO::Serialization {
    Serializer::Serializer(FileSystem::Path fileName, FileSystem::Path path, std::shared_ptr<FileSystem::FileStream> stream)
        : FileName(std::move(fileName))
        , Path(std::move(path))
        , Stream(std::move(stream)) {}

    bool Serializer::IsEnd() const {
        auto test = Stream->Tell();
        auto test1 = Stream->Size();
        return Stream->Tell() == Stream->Size();
    }

    void Serializer::WriteSize(const size_t size) const {
        Stream->Write(&size, sizeof(size_t));
    }

    void Serializer::WriteInt(int value) const {
        Stream->Write(&value, sizeof(int));
    }

    void Serializer::WriteUInt16(uint16_t value) {
        Stream->Write(&value, sizeof(uint16_t));
    }

    void Serializer::WriteUInt32(uint32_t value) const {
        Stream->Write(&value, sizeof(uint32_t));
    }

    void Serializer::WriteUInt64(uint64_t value) const {
        Stream->Write(&value, sizeof(uint64_t));
    }

    void Serializer::WriteFloat(float value) const {
        Stream->Write(&value, sizeof(float));
    }

    void Serializer::WriteBool(bool value) const {
        Stream->Write(&value, sizeof(bool));
    }

    void Serializer::WriteString(const std::string& value) const {
        const size_t valueSize = value.size();

        Stream->Write(&valueSize, sizeof(size_t));
        Stream->Write(value.data(), valueSize);
    }

    void Serializer::WriteByteVector(const std::vector<uint8_t>& data) const {
        auto size = data.size();
        Stream->Write(&size, sizeof(size_t));
        Stream->Write(data.data(), size);
    }

    size_t Serializer::ReadSize() const {
        size_t value;
        Stream->Read(&value, sizeof(size_t));

        return value;
    }

    int Serializer::ReadInt() const {
        int value;
        Stream->Read(&value, sizeof(int));

        return value;
    }

    uint16_t Serializer::ReadUInt16() const {
        uint16_t value;
        Stream->Read(&value, sizeof(uint16_t));

        return value;
    }

    uint32_t Serializer::ReadUInt32() const {
        uint32_t value;
        Stream->Read(&value, sizeof(uint32_t));

        return value;
    }

    uint64_t Serializer::ReadUInt64() const {
        uint64_t value;
        Stream->Read(&value, sizeof(uint64_t));

        return value;
    }

    float Serializer::ReadFloat() const {
        float value;
        Stream->Read(&value, sizeof(float));

        return value;
    }

    bool Serializer::ReadBool() const {
        bool value;
        Stream->Read(&value, sizeof(bool));

        return value;
    }

    std::string Serializer::ReadString() const {
        size_t size;
        std::string value;
        Stream->Read(&size, sizeof(size_t));

        value.resize(size);
        Stream->Read(value.data(), size);

        return value;
    }

    std::vector<uint8_t> Serializer::ReadByteVector() const {
        size_t size;
        Stream->Read(&size, sizeof(size_t));

        std::vector<uint8_t> value(size);
        Stream->Read(value.data(), size);

        return value;
    }
}
