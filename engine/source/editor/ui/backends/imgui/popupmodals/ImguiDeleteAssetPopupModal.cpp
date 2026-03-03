//
// Created by Akira Mujawar on 02/03/26.
//

#include "ImguiDeleteAssetPopupModal.hpp"
#include "ImguiAPI.hpp"
#include "log.hpp"
#include "IO.hpp"

namespace MeowEngine::Editor::UI {
    ImguiDeleteAssetPopupModal::ImguiDeleteAssetPopupModal(const std::string_view& assetPath)
    : AssetPath(assetPath){
        FileSystem::Path path(assetPath);
        TitleText = "Delete " + path.GetName().GetRawString() + "?";
        
        MeowEngine::Log("ImguiDeleteAssetPopupModal", "Created");
    }
    
    ImguiDeleteAssetPopupModal::~ImguiDeleteAssetPopupModal() {
        ImGui::CloseCurrentPopup();
        
        MeowEngine::Log("ImguiDeleteAssetPopupModal", "Destroyed");
    }
    
    bool ImguiDeleteAssetPopupModal::Draw() {
        // ideally on construction this should be called for renaming
        // since its inside popup menu we bring it outside when rendering and open popup
        if(!ImGui::IsPopupOpen(TitleText.c_str())) {
            ImGui::OpenPopup(TitleText.c_str());
        }
        
        bool needToBeClosed = false;
    
        // always center this popup modal when appearing
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    
        if(ImGui::BeginPopupModal(TitleText.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)) {
            ImGui::Text("This file will be deleted.\nThis operation cannot be undone!");
            ImGui::Separator();
            
            if (ImGui::Button("OK", ImVec2(120, 0))) {
                FileSystem::FileSystem::Remove(AssetPath.c_str());
                needToBeClosed = true;
            }
            
            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();
    
            // return true to close the window and clear the object from memory
            if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                needToBeClosed = true;
            }
            
            ImGui::EndPopup();
        }
    
        return needToBeClosed;
    }
}