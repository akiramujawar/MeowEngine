//
// Created by Akira Mujawar on 22/02/26.
//

#include "imgui_project_setting_panel.hpp"
#include "log.hpp"

namespace MeowEngine::Runtime {
    ImguiProjectSettingPanel::ImguiProjectSettingPanel()
        : WindowFlags(ImGuiWindowFlags_NoCollapse), IsActive(false) {
        PT_PROFILE_ALLOC("ImguiProjectSettingPanel", sizeof(ImguiProjectSettingPanel))
    }

    ImguiProjectSettingPanel::~ImguiProjectSettingPanel() {
        PT_PROFILE_FREE("ImguiProjectSettingPanel")
    }

    void ImguiProjectSettingPanel::Draw() {
        ImGui::Begin("Project Settings", &IsActive);
        {
            ImGui::Text("Demo Log 1");
            ImGui::Text("Demo Log 2");

            ImGui::End();
        }
    }
}