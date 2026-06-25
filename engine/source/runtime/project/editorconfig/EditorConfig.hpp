//
// Created by Akira Mujawar on 23/06/26.
//

#ifndef MEOWENGINE_EDITORCONFIG_HPP
#define MEOWENGINE_EDITORCONFIG_HPP


#include <string>

#include "Public/Core/Forward.hpp"

namespace MeowEngine::Runtime {
    struct EditorConfig {
        // engine root path
        // handles for asset thumbnails
        void Load(const Path& path);

        std::string EngineRootPath;
    };
}


#endif //MEOWENGINE_EDITORCONFIG_HPP