//
// Created by Akira Mujawar on 15/06/26.
//

#ifndef MEOWENGINE_MESHASSETIMPORTER_HPP
#define MEOWENGINE_MESHASSETIMPORTER_HPP

#include <string>
#include "Public/Core/Forward.hpp"

namespace MeowEngine::Asset {
    class MeshAssetImporter {
    public:
        static void Import(const Path& filePath, const Path& importToFolderPath);
    };
}


#endif //MEOWENGINE_MESHASSETIMPORTER_HPP