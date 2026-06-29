//
// Created by Akira Mujawar on 13/07/24.
//

#include <ImGuiInspectorPanel.hpp>

#include <ImguiAPI.hpp>
#include <log.hpp>

#include <reflection_macro_wrapper.hpp>
#include <ImguiInputExtension.hpp>

#include <RenderContext.hpp>
#include <RenderUIData.hpp>

#include <CommandQueue.hpp>
#include <ReflectionPropertyChangeCommand.hpp>
#include "AddComponentCommand.hpp"

namespace MeowEngine::Editor {
    ImGuiInspectorPanel::ImGuiInspectorPanel() {

    }

    ImGuiInspectorPanel::~ImGuiInspectorPanel() {

    }

    void ImGuiInspectorPanel::Init() {

    }

    void ImGuiInspectorPanel::Draw(Rendering::RenderContext& renderContext)
    {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoCollapse;

        ImGui::Begin("Inspector", &CanDrawPanel); {
            ShowAddComponentPopup(renderContext);
            ShowComponents(renderContext);

            ImGui::End();
        }
    }

    void ImGuiInspectorPanel::ShowAddComponentPopup(const Rendering::RenderContext& renderContext) {
        // show button
        if (renderContext.UIData->LastSelectedEntity.GetIsValid()) {
            float headerHeight = ImGui::GetTextLineHeightWithSpacing() * 1.2f;
            const std::string& addComponentText = "Add Component + ";
            const ImVec2 createButtonSize(ImGui::CalcTextSize(addComponentText.c_str()).x, headerHeight);
            if (ImGui::Button(addComponentText.c_str(), createButtonSize)) {
                ImGui::OpenPopup("ShowCreateAssetPopupMenu");
            }
        }

        // show popup menu for different types of items which can be created
        if (ImGui::BeginPopup("ShowCreateAssetPopupMenu")) {
            auto compNames = GetReflection().GetComponentNames();
            for (auto& component : compNames) {
                if(ImGui::MenuItem(component.c_str())) {
                    renderContext.CommandQueue->Push(
                        Messaging::ThreadType::MAIN,
                        std::make_unique<Messaging::AddComponentCommand>(renderContext.UIData->LastSelectedEntity, component)
                    );
                }
            }


            ImGui::EndPopup();
        }
    }

    void ImGuiInspectorPanel::ShowComponents(const Rendering::RenderContext& renderContext) {
        // if selected entity
        for (const auto& data : renderContext.UIData->LastSelectedEntityComponents) {
            if (ImGui::CollapsingHeader(data.Name.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
                ReflectionPropertyChange* change = ImGuiInputExtension::ShowProperty(
                    data.Name,
                    data.DataObject,
                    true
                );

                if (change != nullptr) {
                    change->Handle = renderContext.UIData->LastSelectedEntity;
                    change->ComponentType = data.Type;

                    renderContext.CommandQueue->Push(
                        Messaging::ThreadType::MAIN,
                        std::make_unique<Messaging::ReflectionPropertyChangeCommand>(change)
                    );
                }

                ImGui::Spacing();
            }
        }

        // TODO: for this we need to track last selected item or type
        // if selected file
        // draw for file
    }
}
