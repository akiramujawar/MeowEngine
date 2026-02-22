//
// Created by Akira Mujawar on 14/07/24.
//

#ifndef MEOWENGINE_IMGUI_CONSOLE_PANEL_HPP
#define MEOWENGINE_IMGUI_CONSOLE_PANEL_HPP

#include "imgui_wrapper.hpp"

namespace MeowEngine::Runtime {
    struct ImGuiConsolePanel {
        ImGuiConsolePanel();
        ~ImGuiConsolePanel();

        void Draw();

    private:
        bool IsActive;
        ImGuiWindowFlags WindowFlags;
    };
}


#endif //MEOWENGINE_IMGUI_CONSOLE_PANEL_HPP
