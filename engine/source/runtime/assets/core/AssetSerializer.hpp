//
// Created by Akira Mujawar on 05/03/26.
//

#ifndef MEOWENGINE_ASSETIMPORTER_HPP
#define MEOWENGINE_ASSETIMPORTER_HPP

#include <string_view>

#include "Public/Core/Forward.hpp"
#include "AssetHeader.hpp"

namespace MeowEngine::Asset {
    /**
     * Reads asset header or writes asset header + given data
     */
    class AssetSerializer {
    public:
        static void Serialize(const std::string_view& importPath, const std::string_view& savePath);
        static bool Deserialize(const Path& path, AssetHeader& header);
    };
}


#endif //MEOWENGINE_ASSETIMPORTER_HPP