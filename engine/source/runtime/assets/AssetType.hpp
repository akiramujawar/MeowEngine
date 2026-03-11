//
// Created by Akira Mujawar on 10/03/26.
//

#ifndef MEOWENGINETEST2_ASSETTYPE_HPP
#define MEOWENGINETEST2_ASSETTYPE_HPP

namespace MeowEngine::Runtime::Asset {
    enum class AssetType : int{
        // misc / core
        UNKNOWN = 0,
        PROJECT = 1,

        // file types
        TEXTURE = 101,
        MESH = 102,

        // engine specific
        WORLD = 201,
        MATERIAL = 202
    };
}

#endif //MEOWENGINETEST2_ASSETTYPE_HPP