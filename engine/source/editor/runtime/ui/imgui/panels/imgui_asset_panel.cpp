//
// Created by Akira Mujawar on 22/02/26.
//

#include "imgui_asset_panel.hpp"
#include "log.hpp"

namespace MeowEngine::Runtime {
    ImguiAssetPanel::ImguiAssetPanel()
        : WindowFlags(ImGuiWindowFlags_NoCollapse), IsActive(false) {
        PT_PROFILE_ALLOC("ImguiAssetPanel", sizeof(ImguiAssetPanel))
    }

    ImguiAssetPanel::~ImguiAssetPanel() {
        PT_PROFILE_FREE("ImguiAssetPanel")
    }

    void ImguiAssetPanel::Draw() {
        ImGui::Begin("Assets", &IsActive);
        {
            ImGui::Text("Demo Log 1");
            ImGui::Text("Demo Log 2");

            ImGui::End();
        }
    }
}