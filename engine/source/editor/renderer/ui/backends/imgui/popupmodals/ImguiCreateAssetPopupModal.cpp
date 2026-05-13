//
// Created by Akira Mujawar on 27/02/26.
//

#include "ImguiCreateAssetPopupModal.hpp"
#include "ImguiAPI.hpp"
#include "log.hpp"
#include "IO.hpp"
#include "selection_data.hpp"

namespace {
    /**
     * Only allow alphabets & numbers
     * @param data
     * @return
     */
    int FilterInputText(ImGuiInputTextCallbackData* data) {
        if (data->EventChar >= 'a' && data->EventChar <= 'z') {
            return 0;
        }
        else if (data->EventChar >= 'A' && data->EventChar <= 'Z') {
            return 0;
        }
        else if(data->EventChar >= '0' && data->EventChar <= '9') {
            return 0;
        }
        
        return 1;
    }
}

namespace MeowEngine::Editor::UI {
    
    ImguiCreateAssetPopupModal::ImguiCreateAssetPopupModal(const std::string_view& title, const AssetCreateType& createType)
            : TitleText(title)
            , AssetType(createType){
        
        InputText.resize(32);
        
        MeowEngine::Log("ImguiCreateAssetPopup", "Created");
    }
    
    ImguiCreateAssetPopupModal::~ImguiCreateAssetPopupModal() {
        ImGui::CloseCurrentPopup();
        MeowEngine::Log("ImguiCreateAssetPopup", "Destroyed");
    }
    
    bool ImguiCreateAssetPopupModal::Draw(const SelectionData& selectionData) {
        // ideally on construction this should be called for renaming
        // since its inside popup menu we bring it outside when rendering and open popup
        if(!ImGui::IsPopupOpen(TitleText.c_str())) {
            ImGui::OpenPopup(TitleText.c_str());
        }

        bool needToBeClosed = false;
    
        // always center this popup modal when appearing
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        
        if(ImGui::BeginPopupModal(TitleText.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize)) {
            // show input text for update
            ImGui::PushItemWidth(-FLT_MIN);
            if(ImGui::InputText("##CreateAssetPopupModalInput",
                             InputText.data(),
                             InputText.size(),
                             ImGuiInputTextFlags_CallbackCharFilter,
                             FilterInputText)) {
                // TODO: any verifications for the name check here
            }
            ImGui::PopItemWidth();
            ImGui::Separator();
            
            // create the asset with given asset name
            if(ImGui::Button("Create", ImVec2(120, 0))) {
                switch (AssetType) {
                    case AssetCreateType::FOLDER: {
                        FileSystem::Path path {selectionData.SelectedDirectoryPath};
                        FileSystem::Path assetName {InputText};
        
                        FileSystem::FileSystem::CreateDirectory(path + assetName);
                        
                        break;
                    }
                    case AssetCreateType::WORLD:
                        break;
                    default:
                        break;
                }
                
                needToBeClosed = true;
            }
    
            ImGui::SameLine();
            
            // return true to close the window and clear the object from memory
            if(ImGui::Button("Close", ImVec2(120, 0))) {
                needToBeClosed = true;
            }
        
            ImGui::EndPopup();
        }
    
        return needToBeClosed;
    }
    
}