//
// Created by Akira Mujawar on 01/07/26.
//

#ifndef MEOWENGINE_EDITORASSETCONFIGTYPE_HPP
#define MEOWENGINE_EDITORASSETCONFIGTYPE_HPP
#include <cstdint>

namespace MeowEngine::Messaging {
    enum class EditorAssetHandleType {
        UNKNOWN_ICON,
        PROJECT_ICON,
        FOLDER_ICON,
        HPP_ICON,
        CPP_ICON,
        SHADER_ICON,
        WORLD_ICON,
        MESH_ICON,
        TEXTURE_ICON,

        PLAY_BUTTON_ICON,
        STOP_BUTTON_ICON,
        PAUSE_BUTTON_ICON,
        UNPAUSE_BUTTON_ICON
    };
}
#endif //MEOWENGINE_EDITORASSETCONFIGTYPE_HPP