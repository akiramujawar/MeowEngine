//
// Created by Akira Mujawar on 14/07/24.
//

#ifndef MEOWENGINE_IMGUIWORLDVIEWPANEL_HPP
#define MEOWENGINE_IMGUIWORLDVIEWPANEL_HPP

#include "imgui_wrapper.hpp"
#include "window_size.hpp"

namespace MeowEngine::Runtime {

    struct ImGuiWorldViewPanel {
        ImGuiWorldViewPanel();
        ~ImGuiWorldViewPanel();

        void Draw(void* frameBufferId, const float& inFps);

    private:
        bool IsActive;
        bool IsFocused; // soon come up with good naming conventions

        ImGuiWindowFlags WindowFlags;
        WindowSize SceneViewportSize;
    };
}


#endif //MEOWENGINE_IMGUIWORLDVIEWPANEL_HPP
