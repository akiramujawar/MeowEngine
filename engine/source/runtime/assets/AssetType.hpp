//
// Created by Akira Mujawar on 10/03/26.
//

#ifndef MEOWENGINETEST2_ASSETTYPE_HPP
#define MEOWENGINETEST2_ASSETTYPE_HPP

namespace MeowEngine::Asset {
    enum class AssetType : int {
        // misc / core
        UNKNOWN = 0,
        PROJECT = 1,
        FOLDER = 2,
        HPP = 3,
        CPP = 4,
        SHADER = 5,

        // import types
        TEXTURE = 101,
        MESH = 102,

        // engine specific
        WORLD = 201,

        // rendering
        MATERIAL = 301,

        // physics
        PHYSICS_MATERIAL = 401
    };
}

#endif //MEOWENGINETEST2_ASSETTYPE_HPP