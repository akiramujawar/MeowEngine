//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_IMGUI_ASSET_PANEL_HPP
#define MEOWENGINE_IMGUI_ASSET_PANEL_HPP


#include "imgui_wrapper.hpp"

namespace MeowEngine::Runtime {
    struct ImguiAssetPanel {
        ImguiAssetPanel();
        ~ImguiAssetPanel();

        void Draw();

    private:
        bool IsActive;
        ImGuiWindowFlags WindowFlags;
    };
}


#endif //MEOWENGINE_IMGUI_ASSET_PANEL_HPP
