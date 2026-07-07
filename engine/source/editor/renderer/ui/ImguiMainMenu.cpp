//
// Created by Akira Mujawar on 30/06/26.
//

#include "ImguiMainMenu.hpp"

#include <imgui_internal.h>

#include "ImguiAPI.hpp"
#include "RenderContext.hpp"

#include "CommandQueue.hpp"
#include "OpenURLCommand.hpp"
#include "SetGameplayStateCommand.hpp"

#include "GameplayState.hpp"

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
            ImVec2 buttonSize(100, 50);
            auto centerX = ImGui::GetCursorPosX() + (totalSpace.x - buttonSize.x) * 0.5f;

            ImGui::SameLine(centerX);
            if (ImGui::ArrowButton("StartSimulating", ImGuiDir_Right)) {
                renderContext.CommandQueue->Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SetGameplayStateCommand>(Runtime::GameplayState::SIMULATE)
                );
            }

            // ImGui::ImageButton()
            ImGui::SameLine();
            if (ImGui::Button("Pause")) {
                renderContext.CommandQueue->Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SetGameplayStateCommand>(Runtime::GameplayState::PAUSE)
                );
            }

            ImGui::EndChild();
        }
    }
}
