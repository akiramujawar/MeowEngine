//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_SERIALIZER_HPP
#define MEOWENGINETEST2_SERIALIZER_HPP

#include <cstdlib>

#include <FileStream.hpp>

namespace MeowEngine::Core::IO::Serialization {
    class Serializer {
    public:
        explicit Serializer(FileSystem::FileStream& stream);

        void WriteSize(size_t size) const;
        void WriteInt(int value) const;
        void WriteUInt16(uint16_t value);
        void WriteUInt32(uint32_t value) const;
        void WriteUInt64(uint64_t value) const;
        void WriteFloat(float value) const;
        void WriteString(const std::string& value) const;
        void WriteBool(bool value) const;

        size_t ReadSize();
        int ReadInt();
        uint32_t ReadUInt32();
        uint64_t ReadUInt64();
        float ReadFloat();
        std::string& ReadString();
        bool ReadBool();

    private:
        FileSystem::FileStream& Stream;
    };
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