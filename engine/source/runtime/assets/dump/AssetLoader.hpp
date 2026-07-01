//
// Created by Akira Mujawar on 11/09/22.
//

#ifndef MEOWENGINE_ASSETLOADER_HPP
#define MEOWENGINE_ASSETLOADER_HPP

#include "MeshAsset.hpp"
#include <string>
#include "BitmapAsset.hpp"

namespace MeowEngine::assets {
    std::string LoadTextFile(const std::string& path);
    Asset::MeshAsset LoadObjFile(const std::string& path);
    Asset::BitmapAsset LoadBitmap(const std::string& path);
} // namespace MeowEngine::assets;

#endif //MEOWENGINE_ASSETLOADER_HPP
