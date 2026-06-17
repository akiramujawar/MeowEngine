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
            // if selected entity
            for (const auto& data : renderContext.UIData->LastSelectedEntityComponents) {
                if (ImGui::CollapsingHeader(data.Name.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
                    ReflectionPropertyChange* change = ImGuiInputExtension::ShowProperty(
                        data.Name,
                        data.DataObject,
                        true
                    );

                    if (change != nullptr) {
                        change->GUID = renderContext.UIData->LastSelectedEntity;
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

            ImGui::End();
        }
    }
}
