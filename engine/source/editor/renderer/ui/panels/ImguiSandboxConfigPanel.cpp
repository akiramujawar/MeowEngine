//
// Created by Akira Mujawar on 22/02/26.
//

#include "ImguiSandboxConfigPanel.hpp"


#include "log.hpp"
#include "MeowService.hpp"
#include "CommandQueue.hpp"
#include "ImguiAssetDragDrop.hpp"
#include "SetSandboxAssetHandleConfigCommand.hpp"

namespace MeowEngine::Editor {
    ImguiSandboxConfigPanel::ImguiSandboxConfigPanel()
        : WindowFlags(ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing), IsActive(true) {
        PT_PROFILE_ALLOC("ImguiProjectSettingPanel", sizeof(ImguiSandboxConfigPanel))
    }

    ImguiSandboxConfigPanel::~ImguiSandboxConfigPanel() {
        PT_PROFILE_FREE("ImguiProjectSettingPanel")
    }

    void ImguiSandboxConfigPanel::Draw() {
        if(!IsActive) {
            return;
        }

        ImGui::Begin("Sandbox Settings", &IsActive, WindowFlags);
        {
            ImGui::AlignTextToFramePadding();
            ImGui::Text("%s", "Launch World Path");
            ImGui::SameLine();
            ImGui::SetCursorPosX(200);
            float availableSpace = ImGui::GetContentRegionAvail().x;
            ImGui::SetNextItemWidth(availableSpace);

            ImGui::Button("Drag n Drop", ImVec2(ImGui::GetContentRegionAvail().x, 0));

            Asset::AssetHandle handle;
            ImguiAssetDragDrop::DropAssetOnAssetHandleInput(handle);

            if (handle.GetIsValid()) {
                MeowService().CommandQueue.Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SetSandboxAssetHandleConfigCommand>(handle)
                );
            }

            ImGui::End();
        }
    }
}
