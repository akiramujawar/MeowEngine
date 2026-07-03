//
// Created by Akira Mujawar on 14/07/24.
//

#include "ImguiWorldViewPanel.hpp"

#include "log.hpp"
#include "Public/Math.hpp"
#include <SDL_events.h>

#include "EventBus.hpp"
#include "MeowService.hpp"
#include "UserDeviceInputType.hpp"
#include "RenderCommand.hpp"
#include "EventContainer.hpp"
#include "RenderContext.hpp"
#include "RenderUIData.hpp"

namespace MeowEngine::Editor {

    ImGuiWorldViewPanel::ImGuiWorldViewPanel()
        : WindowFlags(ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_UnsavedDocument), IsActive(false),
          IsFocused(true) {
        PT_PROFILE_ALLOC("ImGuiWorldRenderPanel", sizeof(ImGuiWorldViewPanel));
    }

    ImGuiWorldViewPanel::~ImGuiWorldViewPanel() {
        PT_PROFILE_FREE("ImGuiWorldRenderPanel");
    }

    void ImGuiWorldViewPanel::Init() {}

    void ImGuiWorldViewPanel::Draw(Rendering::RenderContext& renderContext) {

        ImGui::Begin("World View", &IsActive, WindowFlags);
        {
            // check for panel focus
            const bool isFocused = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
                                   ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
            if (isFocused != IsFocused) {
                IsFocused = isFocused;

                MeowService().EventBus.Enqueue(Messaging::SceneFocusEvent{IsFocused});
            }

            ImVec2 viewportPos  = ImGui::GetCursorScreenPos();
            ImVec2 viewportSize = ImGui::GetContentRegionAvail();

            ImGui::BeginChild("GameRender");
            {
                // TODO: use event system here
                if ((uint32_t) viewportSize.x != SceneViewportSize.Width ||
                    (uint32_t) viewportSize.y != SceneViewportSize.Height) {

                    MeowService().EventBus.Enqueue(Messaging::SceneViewportResizeEvent{
                        viewportSize.x,
                        viewportSize.y
                    });
                }

                auto frameBufferID = Rendering::RenderCommand::GetSceneFrameBuffer().GetFrameTexture();
                ImGui::Image(
                    reinterpret_cast<ImTextureID>(frameBufferID) ,
                    viewportSize,
                    ImVec2(0, 1),
                    ImVec2(1, 0)
                );

                ImGui::EndChild();
            }

            ImGui::SetCursorScreenPos(viewportPos);
            ImGui::BeginChild("SceneUI", viewportSize, false, ImGuiWindowFlags_NoBackground); {
                float fontSize = 2;
                float offset = 10;
                auto fps = std::to_string(renderContext.UIData->CurrentFPS);
                auto textSize =  ImGui::CalcTextSize(fps.c_str());
                ImVec2 textPos = ImVec2(viewportSize.x - textSize.x * fontSize - offset , offset);
                ImGui::SetCursorPos(textPos);
                ImGui::SetWindowFontScale(fontSize);
                ImGui::Text("%s", fps.c_str());
                ImGui::SetWindowFontScale(1.0f);

                ImGui::EndChild();
            }

            ImGui::End();
        }

    }
}
