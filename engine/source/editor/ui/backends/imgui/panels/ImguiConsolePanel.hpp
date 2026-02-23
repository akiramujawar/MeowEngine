//
// Created by Akira Mujawar on 14/07/24.
//

#ifndef MEOWENGINE_IMGUICONSOLEPANEL_HPP
#define MEOWENGINE_IMGUICONSOLEPANEL_HPP

#include "ImguiAPI.hpp"

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


#endif //MEOWENGINE_IMGUICONSOLEPANEL_HPP
