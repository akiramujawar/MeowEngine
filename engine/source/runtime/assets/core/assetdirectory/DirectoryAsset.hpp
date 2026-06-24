//
// Created by Akira Mujawar on 24/06/26.
//

#ifndef MEOWENGINE_DIRECTORYASSET_HPP
#define MEOWENGINE_DIRECTORYASSET_HPP

#include "Public/Core/Include.hpp"
#include "AssetHandle.hpp"
#include "AssetType.hpp"

namespace MeowEngine::Asset {
    struct DirectoryAsset {
        // DirectoryAsset();

        bool IsFolder;

        Path RelativePath;
        Path AbsolutePath;
        String Name;
        AssetType Type;
        AssetHandle ThumbnailHandle;
        AssetHandle FileHandle;
    };

    // renderer will use asset handle to create gpu
    // where as extractor will call AssetManager.AsyncLoad and return invalid handle until loaded
    // AsyncLoad will queue up loading
    // we preload all the thumbnails in asset database
    // asset database will give us thumbnails, for this special case thumbnails will be preloaded in cache
}


#endif //MEOWENGINE_DIRECTORYASSET_HPP