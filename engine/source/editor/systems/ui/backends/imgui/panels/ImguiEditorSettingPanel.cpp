//
// Created by Akira Mujawar on 22/02/26.
//

#include "ImguiEditorSettingPanel.hpp"
#include "log.hpp"

namespace MeowEngine::Runtime {
    ImguiEditorSettingPanel::ImguiEditorSettingPanel()
        : WindowFlags(ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing), IsActive(false) {
        PT_PROFILE_ALLOC("ImguiEditorSettingPanel", sizeof(ImguiEditorSettingPanel))
    }

    ImguiEditorSettingPanel::~ImguiEditorSettingPanel() {
        PT_PROFILE_FREE("ImguiEditorSettingPanel")
    }

    void ImguiEditorSettingPanel::Draw() {
        ImGui::Begin("Editor Settings", &IsActive, WindowFlags);
        {
            ImGui::Text("Demo Log 1");
            ImGui::Text("Demo Log 2");

            ImGui::End();
        }
    }
}