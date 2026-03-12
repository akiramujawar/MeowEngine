//
// Created by Akira Mujawar on 03/03/26.
//

#ifndef MEOWENGINE_MEOWASSETHEADER_HPP
#define MEOWENGINE_MEOWASSETHEADER_HPP

#include <cstdint>

namespace MeowEngine::Runtime::Asset {

// pack results in placement of the members one after another in memory
// remember how we used to set png sizes to multiples of 2?
// this for that as memeory likes to ready in multiples of sizes (4 bytes / 8 bytes atc..)
// so naturually even if we create structu with say 20 bytes and each of them is randomly
// 1 byte 3 bytes 2 bytes arragned, compiler add
// it is recommened to pack for files to avoid reading data by different compilers. We need exact values unaffected by compiler
#pragma pack(push, 1)
    struct AssetHeader {
        char Magic[4]{};

        uint32_t Version{};
        uint64_t UUID{};
        int Type;

        uint64_t SettingIndicator{};
        uint64_t SettingSize{};

        uint64_t DataIndicator{};
        uint64_t DataSize{};

        AssetHeader()
        : Version(0)
        , UUID(0)
        , Type(0)
        , SettingIndicator(0)
        , SettingSize(0)
        , DataIndicator(0)
        , DataSize(0) {}

        AssetHeader(uint64_t uuid, int type)
        : Version(1)
        , UUID(uuid)
        , Type(type)
        , SettingIndicator(0)
        , SettingSize(0)
        , DataIndicator(0)
        , DataSize(0) {
            memcpy(Magic, "MEOW", 4); // direct copy without include \0
        }
    };
#pragma pack(pop)

}

#endif //MEOWENGINE_MEOWASSETHEADER_HPP