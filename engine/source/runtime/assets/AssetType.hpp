//
// Created by Akira Mujawar on 10/03/26.
//

#ifndef MEOWENGINETEST2_ASSETTYPE_HPP
#define MEOWENGINETEST2_ASSETTYPE_HPP

namespace MeowEngine::Runtime::Asset {
    enum class AssetType : int{
        UNKNOWN,
        TEXTURE,
        MESH,
        WORLD,
        MATERIAL
    };
}

#endif //MEOWENGINETEST2_ASSETTYPE_HPP