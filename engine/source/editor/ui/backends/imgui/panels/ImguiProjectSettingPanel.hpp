//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_IMGUIPROJECTSETTINGPANEL_HPP
#define MEOWENGINE_IMGUIPROJECTSETTINGPANEL_HPP


#include "ImguiAPI.hpp"

namespace MeowEngine::Runtime {
    struct ImguiProjectSettingPanel {
        ImguiProjectSettingPanel();
        ~ImguiProjectSettingPanel();

        void Draw();

    private:
        bool IsActive;
        ImGuiWindowFlags WindowFlags;
    };
}


#endif //MEOWENGINE_IMGUIPROJECTSETTINGPANEL_HPP
