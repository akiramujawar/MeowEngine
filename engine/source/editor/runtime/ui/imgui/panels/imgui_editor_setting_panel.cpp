//
// Created by Akira Mujawar on 22/02/26.
//

#include "imgui_editor_setting_panel.hpp"
#include "log.hpp"

namespace MeowEngine::Runtime {
    ImguiEditorSettingPanel::ImguiEditorSettingPanel()
        : WindowFlags(ImGuiWindowFlags_NoCollapse), IsActive(false) {
        PT_PROFILE_ALLOC("ImguiEditorSettingPanel", sizeof(ImguiEditorSettingPanel))
    }

    ImguiEditorSettingPanel::~ImguiEditorSettingPanel() {
        PT_PROFILE_FREE("ImguiEditorSettingPanel")
    }

    void ImguiEditorSettingPanel::Draw() {
        ImGui::Begin("Editor Settings", &IsActive);
        {
            ImGui::Text("Demo Log 1");
            ImGui::Text("Demo Log 2");

            ImGui::End();
        }
    }
}