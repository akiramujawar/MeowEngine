//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_SERIALIZER_HPP
#define MEOWENGINETEST2_SERIALIZER_HPP

#include <cstdlib>

namespace MeowEngine::Core::IO::Serialization {
    class Serializer {
    public:
        void WriteInt();
        void WriteUInt32();
        void WriteUInt64();
        void WriteFloat();
        void WriteString();
        void WriteBool();

        void ReadInt();
        void ReadUInt32();
        void ReadUInt64();
        void ReadFloat();
        void ReadString();
        void ReadBool();
    };
}

#endif //MEOWENGINETEST2_SERIALIZER_HPP