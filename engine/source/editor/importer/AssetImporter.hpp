//
// Created by Akira Mujawar on 05/03/26.
//

#ifndef MEOWENGINE_ASSETIMPORTER_HPP
#define MEOWENGINE_ASSETIMPORTER_HPP
#include <string_view>

namespace MeowEngine::Editor {
    class AssetImporter {
    public:
        static void Import(const std::string_view& importPath, const std::string_view& savePath);

    };
}


#endif //MEOWENGINE_ASSETIMPORTER_HPP