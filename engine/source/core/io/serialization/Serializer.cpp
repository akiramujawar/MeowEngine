//
// Created by Akira Mujawar on 11/03/26.
//

#include "Serializer.hpp"

#include <FileStream.hpp>

namespace MeowEngine::Core::IO::Serialization {
    Serializer::Serializer(FileSystem::FileStream& stream)
        : Stream(stream) {}

    void Serializer::WriteSize(const size_t size) const {
        Stream.Write(&size, sizeof(size_t));
    }

    void Serializer::WriteInt(int value) const {
        Stream.Write(&value, sizeof(int));
    }

    void Serializer::WriteUInt16(uint16_t value) {
        Stream.Write(&value, sizeof(uint16_t));
    }

    void Serializer::WriteUInt32(uint32_t value) const {
        Stream.Write(&value, sizeof(uint32_t));
    }

    void Serializer::WriteUInt64(uint64_t value) const {
        Stream.Write(&value, sizeof(uint64_t));
    }

    void Serializer::WriteFloat(float value) const {
        Stream.Write(&value, sizeof(float));
    }

    void Serializer::WriteString(const std::string& value) const {
        const size_t valueSize = value.size();

        Stream.Write(&valueSize, sizeof(uint32_t));
        Stream.Write(value.data(), valueSize);
    }

    void Serializer::WriteBool(bool value) const {
        Stream.Write(&value, sizeof(bool));
    }
}
