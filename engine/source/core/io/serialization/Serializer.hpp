//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_SERIALIZER_HPP
#define MEOWENGINETEST2_SERIALIZER_HPP

#include <memory>
#include <cstdlib>

#include "FileStream.hpp"
#include "Path.hpp"

namespace MeowEngine::Core::IO::Serialization {
    struct Serializer {
    public:
        explicit Serializer(FileSystem::Path fileName, FileSystem::Path path, std::shared_ptr<FileSystem::FileStream> stream);

        /**
         * Is all data read? then stop reading, please :)
         * @return
         */
        bool IsEnd() const;

        void WriteSize(size_t size) const;
        void WriteInt(int value) const;
        void WriteUInt16(uint16_t value);
        void WriteUInt32(uint32_t value) const;
        void WriteUInt64(uint64_t value) const;
        void WriteFloat(float value) const;
        void WriteBool(bool value) const;
        void WriteString(const std::string& value) const;
        void WriteByteVector(const std::vector<uint8_t>& data) const;

        template <typename Type>
        void Write(const Type& type) const;

        [[nodiscard]] size_t ReadSize() const;
        [[nodiscard]] int ReadInt() const;
        [[nodiscard]] uint16_t ReadUInt16() const;
        [[nodiscard]] uint32_t ReadUInt32() const;
        [[nodiscard]] uint64_t ReadUInt64() const;
        [[nodiscard]] float ReadFloat() const;
        [[nodiscard]] bool ReadBool() const;
        [[nodiscard]] std::string ReadString() const;
        [[nodiscard]] std::vector<uint8_t> ReadByteVector() const;

        template<typename Type>
        Type Read() const;

        [[nodiscard]] FileSystem::Path GetPath() const { return Path; }
        [[nodiscard]] FileSystem::FileMode GetMode() const { return Stream->GetMode(); }
        [[nodiscard]] FileSystem::Path GetFileName() const { return FileName; }

        [[nodiscard]] FileSystem::FileStream& GetStream() const { return *Stream; }

    private:
        FileSystem::Path FileName;
        FileSystem::Path Path;
        // FileSystem::FileMode Mode;

        std::shared_ptr<FileSystem::FileStream> Stream;
    };

    template <typename Type>
    void Serializer::Write(const Type& type) const {
        static_assert(std::is_trivially_copyable_v<Type>, "Raw Write only supports trivially copyable types");

        uint32_t size = sizeof(Type);

        WriteUInt32(size);
        Stream->Write(&type, sizeof(Type));
    }

    template <typename Type>
    Type Serializer::Read() const {
        static_assert(std::is_trivially_copyable_v<Type>, "Raw Read only supports trivially copyable");

        Type value;
        auto size = ReadUInt32();
        Stream->Read(&value, size);

        return value;
    }
}


// World.hpp - representation live world
// WorldSerialized.hpp - only read / write
// takes the file reads and perform actiosn on world.hpp
// takes the world, serializes and saves to file

// AssetResolver.hpp - read write represent
// Bitmap.hpp - representation of texture

// importer & loader for textures, objects and etc...
// serializer for custom types like world, materials, prefabs

// importers = texutres, mesh, meowdata
// loaders = textures, mesh
// serializers = load + serialize = world. materials
// types = textures, world, mesh

#endif //MEOWENGINETEST2_SERIALIZER_HPP