//
// Created by Akira Mujawar on 11/09/22.
//

#ifndef MEOWENGINE_ASSETLOADER_HPP
#define MEOWENGINE_ASSETLOADER_HPP

#include "Mesh.hpp"
#include <string>
#include "Bitmap.hpp"

namespace MeowEngine::assets {
    std::string LoadTextFile(const std::string& path);
    MeowEngine::Mesh LoadObjFile(const std::string& path);
    MeowEngine::Bitmap LoadBitmap(const std::string& path);
} // namespace MeowEngine::assets;

#endif //MEOWENGINE_ASSETLOADER_HPP
