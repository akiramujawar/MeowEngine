//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_IMGUIEDITORSETTINGPANEL_HPP
#define MEOWENGINE_IMGUIEDITORSETTINGPANEL_HPP


#include "imgui_wrapper.hpp"

namespace MeowEngine::Runtime {
    struct ImguiEditorSettingPanel {
        ImguiEditorSettingPanel();
        ~ImguiEditorSettingPanel();

        void Draw();

    private:
        bool IsActive;
        ImGuiWindowFlags WindowFlags;
    };
}



#endif //MEOWENGINE_IMGUIEDITORSETTINGPANEL_HPP
