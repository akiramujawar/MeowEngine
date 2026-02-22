//
// Created by Akira Mujawar on 22/02/26.
//

#include "ImguiProjectSettingPanel.hpp"
#include "log.hpp"

namespace MeowEngine::Runtime {
    ImguiProjectSettingPanel::ImguiProjectSettingPanel()
        : WindowFlags(ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing), IsActive(true) {
        PT_PROFILE_ALLOC("ImguiProjectSettingPanel", sizeof(ImguiProjectSettingPanel))
    }

    ImguiProjectSettingPanel::~ImguiProjectSettingPanel() {
        PT_PROFILE_FREE("ImguiProjectSettingPanel")
    }

    void ImguiProjectSettingPanel::Draw() {
        if(!IsActive) {
            return;
        }

        ImGui::Begin("Project Settings", &IsActive, WindowFlags);
        {
            ImGui::Text("Demo Log 1");
            ImGui::Text("Demo Log 2");

            ImGui::End();
        }
    }
}