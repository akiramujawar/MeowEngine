//
// Created by Akira Mujawar on 28/02/26.
//

#include "ImguiAssetDragDrop.hpp"
#include "ImguiAPI.hpp"
#include "IO.hpp"

namespace MeowEngine::Editor::UI {
    void ImguiAssetDragDrop::DragAsset(const std::string& path, const std::string& name, void* imagePtr) {
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
            // NOTE: remember memory layout for char is ['a','b','c',...,'\0']
            // char is read until it hits '\0'
            // std::string::size() doesn't count '\0' hence we "+1" to calc total size
            ImGui::SetDragDropPayload("DragAndDropAsset", path.c_str(), path.size() + 1); // +1
            
            float textWidth = ImGui::CalcTextSize(name.c_str()).x;
            float imageSize = 64;
            float cursorPositionX = ImGui::GetCursorPosX();
            
            // show asset icon
            if(textWidth > imageSize) {
                float imagePositionX = cursorPositionX + (textWidth - imageSize) * 0.5f;
                ImGui::SetCursorPosX(imagePositionX);
            }
            
            ImGui::Image(imagePtr, ImVec2(imageSize,imageSize));
            
            // show asset name
            if(textWidth < imageSize) {
                float textPositionX = cursorPositionX + (imageSize - textWidth) * 0.5f;
                ImGui::SetCursorPosX(textPositionX);
            }
            
            ImGui::Text("%s", name.c_str());
            
            ImGui::EndDragDropSource();
        }
    }
    
    void ImguiAssetDragDrop::DropAsset(const std::string& moveToPath) {
        if (ImGui::BeginDragDropTarget()) {
            // gets the asset path which needs to be moved & then using "moveToPath"
            // it moves the file/folder to new directory
            if (const ImGuiPayload* payloadVoidPtr = ImGui::AcceptDragDropPayload("DragAndDropAsset")) {
                const char* payloadData = (const char*)payloadVoidPtr->Data;
                FileSystem::Path assetPath {payloadData};
                
                if(FileSystem::FileSystem::IsDirectory(moveToPath.c_str())) {
                    FileSystem::FileSystem::Move(assetPath, moveToPath.c_str());
                }
            }
            
            ImGui::EndDragDropTarget();
        }
    }
}