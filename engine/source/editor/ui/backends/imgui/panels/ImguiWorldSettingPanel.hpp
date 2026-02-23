//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_IMGUIWORLDSETTINGPANEL_HPP
#define MEOWENGINE_IMGUIWORLDSETTINGPANEL_HPP


#include "ImguiAPI.hpp"

namespace MeowEngine::Runtime {
    struct ImguiWorldSettingPanel {
        ImguiWorldSettingPanel();
        ~ImguiWorldSettingPanel();

        void Draw();

    private:
        bool IsActive;
        ImGuiWindowFlags WindowFlags;
    };
}


#endif //MEOWENGINE_IMGUIWORLDSETTINGPANEL_HPP
