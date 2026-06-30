//
// Created by Akira Mujawar on 15/06/26.
//

#ifndef MEOWENGINE_TEXTUREASSETIMPORTER_HPP
#define MEOWENGINE_TEXTUREASSETIMPORTER_HPP

#include <string>
#include "Public/Core/Forward.hpp"

namespace MeowEngine::Asset {
    class TextureAssetImporter {
    public:
        static void Import(const Path& filePath, const Path& importToFolderPath);
    };
}


#endif //MEOWENGINE_TEXTUREASSETIMPORTER_HPP