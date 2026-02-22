//
// Created by Akira Mujawar on 22/02/26.
//

#include "ImguiWorldSettingPanel.hpp"
#include "log.hpp"

namespace MeowEngine::Runtime {
    ImguiWorldSettingPanel::ImguiWorldSettingPanel()
        : WindowFlags(ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing), IsActive(false) {
        PT_PROFILE_ALLOC("ImguiWorldSettingPanel", sizeof(ImguiWorldSettingPanel))
    }

    ImguiWorldSettingPanel::~ImguiWorldSettingPanel() {
        PT_PROFILE_FREE("ImguiWorldSettingPanel")
    }

    void ImguiWorldSettingPanel::Draw() {
        ImGui::Begin("World Settings", &IsActive, WindowFlags);
        {
            ImGui::Text("Demo Log 1");
            ImGui::Text("Demo Log 2");

            ImGui::End();
        }
    }
}