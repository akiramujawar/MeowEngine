//
// Created by Akira Mujawar on 01/07/26.
//

#ifndef MEOWENGINE_TEXTURESERIALIZER_HPP
#define MEOWENGINE_TEXTURESERIALIZER_HPP

#include <cstdlib>
#include <vector>

#include "Public/Core/Forward.hpp"
#include "BitmapAsset.hpp"

namespace MeowEngine::Asset {
    class TextureSerializer {
    public:
        static bool Serialize(const Path& path, const std::vector<uint8_t>& data);
        static bool Deserialize(const Path& path, BitmapAsset& asset);
    };
}


#endif //MEOWENGINE_TEXTURESERIALIZER_HPP