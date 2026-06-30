//
// Created by Akira Mujawar on 14/07/24.
//

#include <ImguiDockerSpace.hpp>

#include "ImguiAPI.hpp"

namespace MeowEngine::Editor {
    ImGuiDockerSpace::ImGuiDockerSpace() {
        // DockSpaceFlags = ImGuiDockNodeFlags_None;
        // WindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        //
        // // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // // because it would be confusing to have two docking targets within each others.
        // //    if (opt_fullscreen)
        // if (true) {
        //     const ImGuiViewport* viewport = ImGui::GetMainViewport();
        //     ImGui::SetNextWindowPos(viewport->WorkPos);
        //     ImGui::SetNextWindowSize(viewport->WorkSize);
        //     ImGui::SetNextWindowViewport(viewport->ID);
        //     ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        //     ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        //
        //     window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
        //                     ImGuiWindowFlags_NoMove;
        //     window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        // } else {
        //     dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        // }
    }

    ImGuiDockerSpace::~ImGuiDockerSpace() {}

    void ImGuiDockerSpace::SetupDockingSpace(Rendering::RenderContext& renderContext) {
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
//    if (opt_fullscreen)
        if (true) {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                            ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        } else {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
//    if (!opt_padding) {
//        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
//    }

        bool isOpen = true;
        ImGui::Begin("DockSpace Demo", &isOpen, window_flags);
        {
//        if (!opt_padding)
//            ImGui::PopStyleVar();
//
//        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

            MainMenu.Draw(renderContext);

            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);



//             if (ImGui::BeginMenuBar()) {
//                 if (ImGui::BeginMenu("File")) {
//                     // Disabling fullscreen would allow the window to be moved to the front of other windows,
//                     // which we can't undo at the moment without finer window depth/z control.
// //                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
// //                ImGui::MenuItem("Padding", NULL, &opt_padding);
// //                ImGui::Separator();
// //
// //                if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
// //                if (ImGui::MenuItem("Flag: NoDockingSplit",         "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0))             { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
// //                if (ImGui::MenuItem("Flag: NoUndocking",            "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0))                { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
// //                if (ImGui::MenuItem("Flag: NoResize",               "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                   { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
// //                if (ImGui::MenuItem("Flag: AutoHideTabBar",         "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))             { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
// //                if (ImGui::MenuItem("Flag: PassthruCentralNode",    "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
// //                ImGui::Separator();
// //
// //                if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
// //                    *p_open = false;
//                     ImGui::EndMenu();
//                 }
//                 ImGui::EndMenuBar();
//             }

            ImGui::End();
        }
    }
}
