//
// Created by Akira Mujawar on 02/03/26.
//

#include "ImguiAssetRenamePopupModal.hpp"
#include "ImguiAPI.hpp"
#include "log.hpp"
#include "IO.hpp"

namespace MeowEngine::Editor::UI {
    ImguiAssetRenamePopupModal::ImguiAssetRenamePopupModal(float x, float y, float width, float height, const std::string_view& assetPath)
    : X(x)
    , Y(y)
    , Width(width)
    , Height(height)
    , AssetPath(assetPath) {
        RenameTextBuffer = FileSystem::Path(AssetPath).GetName().GetRawString();
        MeowEngine::Log("ImguiAssetRenameInput", "Created");
    }
    
    ImguiAssetRenamePopupModal::~ImguiAssetRenamePopupModal() {
        ImGui::CloseCurrentPopup();
        
        MeowEngine::Log("ImguiAssetRenameInput", "Destroyed");
    }
    
    bool ImguiAssetRenamePopupModal::IsSamePath(const std::string& assetPath) {
        return AssetPath == assetPath;
    }
    
    bool ImguiAssetRenamePopupModal::Draw() {
        // ideally on construction this should be called for renaming
        // since its inside popup menu we bring it outside when rendering and open popup
        if(!ImGui::IsPopupOpen("##AssetRenameModal")) {
            ImGui::OpenPopup("##AssetRenameModal");
        }
        
        bool needToBeClosed = false;
    
        ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));
        
        ImGui::SetNextWindowPos(ImVec2(X, Y), ImGuiCond_Appearing, ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(Width, Height), ImGuiCond_Appearing);
        
        // always center this popup modal when appearing
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();

        auto flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDecoration;
    
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_ModalWindowDimBg, IM_COL32(0, 0, 0, 0));
        
        if(ImGui::BeginPopupModal("##AssetRenameModal", nullptr, flags)) {
            ImGui::SetKeyboardFocusHere();
            ImGui::PushItemWidth(-FLT_MIN);
            
            // rename & return close if hit enter
            if (ImGui::InputText("##RenameAsset", RenameTextBuffer.data(), 32, ImGuiInputTextFlags_EnterReturnsTrue)) {
                RenameTextBuffer.resize(strlen(RenameTextBuffer.c_str()));

                
                
                needToBeClosed = true;
            }
            
            ImGui::PopItemWidth();
            
            // stop renaming if clicked anywhere outside input box
            if(ImGui::IsMouseClicked(0) && !ImGui::IsItemHovered()) {
                needToBeClosed = true;
            }
            
            
            ImGui::EndPopup();
        }
    
        
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(4);

        return needToBeClosed;
    }
}