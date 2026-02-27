//
// Created by Akira Mujawar on 27/02/26.
//

#include "ImguiCreateAssetPopupModal.hpp"
#include "ImguiAPI.hpp"
#include "log.hpp"

namespace MeowEngine::Editor::UI {
    
    ImguiCreateAssetPopupModal::ImguiCreateAssetPopupModal(const std::string& createType)
        : CreateTypeString(createType)
        , TitleString("Create "+createType) {
        ImGui::OpenPopup(TitleString.c_str());
        MeowEngine::Log("ImguiCreateAssetPopup", "Created");
    }
    
    ImguiCreateAssetPopupModal::~ImguiCreateAssetPopupModal() {
        ImGui::CloseCurrentPopup();
        MeowEngine::Log("ImguiCreateAssetPopup", "Destroyed");
    }
    
    bool ImguiCreateAssetPopupModal::Draw() {
        bool needToBeClosed = false;
    
        // always center this popup modal when appearing
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(500,300), ImGuiCond_Appearing);
        
        if(ImGui::BeginPopupModal(TitleString.c_str(), nullptr, ImGuiWindowFlags_NoResize)) {
            if(ImGui::Button("Create")) {
                needToBeClosed = true;
            }
        
            if(ImGui::Button("Close")) {
                needToBeClosed = true;
            }
        
            ImGui::EndPopup();
        }
    
        return needToBeClosed;
    }
    
    void ImguiCreateAssetPopupModal::ShowMenuItem(const std::string& name, std::string& createType) {
        if(ImGui::MenuItem(name.c_str())) {
            createType = name;
        }
    }
    
}