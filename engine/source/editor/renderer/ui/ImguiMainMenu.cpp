//
// Created by Akira Mujawar on 30/06/26.
//

#include "ImguiMainMenu.hpp"

#include <imgui_internal.h>

#include "AssetManager.hpp"
#include "ImguiAPI.hpp"
#include "RenderContext.hpp"

#include "CommandQueue.hpp"
#include "ConfigManager.hpp"
#include "OpenURLCommand.hpp"
#include "SetGameplayStateCommand.hpp"

#include "GameplayState.hpp"
#include "MeowService.hpp"
#include "RenderResourceManager.hpp"
#include "RenderUIData.hpp"

namespace MeowEngine::Editor {
    void ImguiMainMenu::Draw(Rendering::RenderContext& renderContext) {
        ImGui::BeginChild("Toolbar", ImVec2(0, 20)); {
            if (ImGui::Button("< Go Back")) {
                renderContext.CommandQueue->Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::OpenUrlCommand>(WebAddress("https://akiramujawar.com"))
                );
            }

            ImGui::SameLine();
            if (ImGui::Button("Github")) {
                renderContext.CommandQueue->Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::OpenUrlCommand>(WebAddress("https://github.com/akiramujawar"))
                );
            }

            ImGui::SameLine();
            if (ImGui::Button("Resume")) {
                renderContext.CommandQueue->Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::OpenUrlCommand>(WebAddress("https://akiramujawar.com/akira_mujawar_engine_programmer_resume.pdf"))
                );
            }

            auto totalSpace = ImGui::GetContentRegionMax();
            ImVec2 buttonSize(20, 20);
            auto centerX = ImGui::GetCursorPosX() + (totalSpace.x - buttonSize.x) * 0.5f;
            auto& resourceManager = renderContext.ResourceManager;
            auto& editorConfig = MeowService().ConfigManager.EditorConfig;

            ImGui::SameLine(centerX);

            auto assetHandle = Asset::AssetHandle::Invalid;

            // select icon
            if (renderContext.UIData->IsSimulating) {
                assetHandle = Asset::AssetHandle::Create(editorConfig.StopButtonIconGuid);
            }
            else {
                assetHandle = Asset::AssetHandle::Create(editorConfig.PlayButtonIconGuid);
            }

            // play / stop button
            if (MeowService().AssetManager.IsLoaded(assetHandle)) {
                Rendering::TextureRenderHandle textureHandle(assetHandle);
                auto imagePtr = resourceManager->GetThumbnailResource(textureHandle).GetTextureID();

                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                ImGui::PushStyleColor(ImGuiCol_Button,        IM_COL32(0,0,0,0));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(0,0,0,0));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive,  IM_COL32(0,0,0,0));

                if (ImGui::ImageButton("##PlayButton", imagePtr, buttonSize)) {
                    renderContext.CommandQueue->Push(
                        Messaging::ThreadType::MAIN,
                        std::make_unique<Messaging::SetGameplayStateCommand>(Runtime::GameplayState::SIMULATE)
                    );
                }

                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);
            }

            ImGui::SameLine();

            // select icon
            if (renderContext.UIData->IsPaused) {
                assetHandle = Asset::AssetHandle::Create(editorConfig.UnPauseButtonIconGuid);
            }
            else {
                assetHandle = Asset::AssetHandle::Create(editorConfig.PauseButtonIconGuid);
            }

            // pause / unpause button
            if (MeowService().AssetManager.IsLoaded(assetHandle)) {
                Rendering::TextureRenderHandle textureHandle(assetHandle);
                auto imagePtr = resourceManager->GetThumbnailResource(textureHandle).GetTextureID();

                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                ImGui::PushStyleColor(ImGuiCol_Button,        IM_COL32(0,0,0,0));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(0,0,0,0));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive,  IM_COL32(0,0,0,0));

                if (ImGui::ImageButton("##PauseButton", imagePtr, ImVec2(buttonSize.x, buttonSize.y))) {
                    renderContext.CommandQueue->Push(
                        Messaging::ThreadType::MAIN,
                        std::make_unique<Messaging::SetGameplayStateCommand>(Runtime::GameplayState::PAUSE)
                    );
                }

                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);
            }

            ImGui::EndChild();
        }
    }
}
