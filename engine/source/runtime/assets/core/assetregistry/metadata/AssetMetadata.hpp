//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST_ASSETMETADATA_HPP
#define MEOWENGINETEST_ASSETMETADATA_HPP

#include <string>

#include "AssetType.hpp"
#include "AssetHandle.hpp"

namespace MeowEngine::Asset {
#pragma pack(push, 1)
    /**
     * Stores uuid and type of file. Can be extended to store thumbnails and much more...
     */
    struct AssetMetadata {
        AssetType Type;
        std::string Path;
        AssetHandle Handle;
    };
#pragma pack(pop)
}

#endif //MEOWENGINETEST_ASSETMETADATA_HPP