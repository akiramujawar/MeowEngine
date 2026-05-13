//
// Created by Akira Mujawar on 14/07/24.
//

#include "ImguiConsolePanel.hpp"
#include "log.hpp"

namespace MeowEngine::Runtime {
    ImGuiConsolePanel::ImGuiConsolePanel()
        : WindowFlags(ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing), IsActive(false) {
        PT_PROFILE_ALLOC("ImGuiLogPanel", sizeof(ImGuiConsolePanel))
    }

    ImGuiConsolePanel::~ImGuiConsolePanel() {
        PT_PROFILE_FREE("ImGuiLogPanel")
    }

    void ImGuiConsolePanel::Draw() {
        ImGui::Begin("Console", &IsActive, WindowFlags);
        {
            ImGui::Text("Demo Log 1");
            ImGui::Text("Demo Log 2");

            ImGui::End();
        }
    }
}