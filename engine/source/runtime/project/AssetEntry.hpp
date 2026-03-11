//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_ASSETENTRY_HPP
#define MEOWENGINETEST2_ASSETENTRY_HPP

#include <string>
#include <AssetType.hpp>

namespace MeowEngine::Runtime::Asset {
#pragma pack(push, 1)
    /**
     * Stores uuid and type of file. Can be extended to store thumbnails and much more...
     */
    struct AssetEntry {
        AssetType Type;
        std::string Path;
    };
#pragma pack(pop)
}

#endif //MEOWENGINETEST2_ASSETENTRY_HPP