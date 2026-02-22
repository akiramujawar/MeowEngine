//
// Created by Akira Mujawar on 22/02/26.
//

#include "imgui_world_setting_panel.hpp"
#include "log.hpp"

namespace MeowEngine::Runtime {
    ImguiWorldSettingPanel::ImguiWorldSettingPanel()
        : WindowFlags(ImGuiWindowFlags_NoCollapse), IsActive(false) {
        PT_PROFILE_ALLOC("ImguiWorldSettingPanel", sizeof(ImguiWorldSettingPanel))
    }

    ImguiWorldSettingPanel::~ImguiWorldSettingPanel() {
        PT_PROFILE_FREE("ImguiWorldSettingPanel")
    }

    void ImguiWorldSettingPanel::Draw() {
        ImGui::Begin("World Settings", &IsActive);
        {
            ImGui::Text("Demo Log 1");
            ImGui::Text("Demo Log 2");

            ImGui::End();
        }
    }
}