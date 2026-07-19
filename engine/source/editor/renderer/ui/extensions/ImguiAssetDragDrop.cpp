//
// Created by Akira Mujawar on 28/02/26.
//

#include "ImguiAssetDragDrop.hpp"
#include "ImguiAPI.hpp"
#include <Public/IO.hpp>

#include "MeowService.hpp"
#include "CommandQueue.hpp"
#include "MoveFileCommand.hpp"

namespace MeowEngine::Editor {
    void ImguiAssetDragDrop::DragAsset(const Asset::DirectoryAsset& asset, const std::string& name, void* imagePtr) {
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
            // NOTE: remember memory layout for char is ['a','b','c',...,'\0']
            // char is read until it hits '\0'
            // std::string::size() doesn't count '\0' hence we "+1" to calc total size
            ImGui::SetDragDropPayload("DragAndDropAsset", &asset, sizeof(Asset::DirectoryAsset)); // +1
            // MeowEngine::Log("Payload Start: ", std::to_string(asset.FileHandle.GetUUID()));
            
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

    bool ImguiAssetDragDrop::DropAssetOnAssetHandleInput(Asset::AssetHandle& asset) {
        bool isDropped = false;
        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payloadVoidPtr = ImGui::AcceptDragDropPayload("DragAndDropAsset")) {
                auto* payloadData = static_cast<Asset::DirectoryAsset*>(payloadVoidPtr->Data);
                // MeowEngine::Log("Payload End: ", std::to_string(payloadData->FileHandle.GetUUID()));
                asset = Asset::AssetHandle::Create(payloadData->FileHandle.GetUUID()); // TODO: check for multithread support

                isDropped = true;
            }
            ImGui::EndDragDropTarget();

        }

        return isDropped;
    }

    bool ImguiAssetDragDrop::DropAssetOnEntityHandleInput(Runtime::EntityHandle& asset) {
        bool isDropped = false;
        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payloadVoidPtr = ImGui::AcceptDragDropPayload("DragAndDropAsset")) {
                MeowEngine::Log("AssetDragDrop::DropAssetOnEntityHandleInput", "Not Implemented");

                isDropped = true;
            }
            ImGui::EndDragDropTarget();

        }

        return isDropped;
    }

    void ImguiAssetDragDrop::DropAssetOnFolder(const std::string& moveToPath) {
        if (ImGui::BeginDragDropTarget()) {
            // gets the asset path which needs to be moved & then using "moveToPath"
            // it moves the file/folder to new directory
            if (const ImGuiPayload* payloadVoidPtr = ImGui::AcceptDragDropPayload("DragAndDropAsset")) {
                auto* payloadData = static_cast<Asset::DirectoryAsset*>(payloadVoidPtr->Data);

                MeowService().CommandQueue.Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::MoveFileCommand>(String(payloadData->AbsolutePath.GetRawString()), String(moveToPath))
                );
            }
            
            ImGui::EndDragDropTarget();
        }
    }

    void ImguiAssetDragDrop::DragEntity(const Runtime::EntityHandle& entity) {
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
            // NOTE: remember memory layout for char is ['a','b','c',...,'\0']
            // char is read until it hits '\0'
            // std::string::size() doesn't count '\0' hence we "+1" to calc total size
            ImGui::SetDragDropPayload("DragAndDropEntity", &entity, sizeof(Runtime::EntityHandle)); // +1

            std::string name = std::to_string(entity.GetGUIDInt());

            ImGui::Text("%s", name.c_str());
            ImGui::EndDragDropSource();
        }
    }

    bool ImguiAssetDragDrop::DropEntity(Runtime::EntityHandle& entity) {
        bool isDropped = false;

        if (ImGui::BeginDragDropTarget()) {
            // gets the asset path which needs to be moved & then using "moveToPath"
            // it moves the file/folder to new directory
            if (const ImGuiPayload* payloadVoidPtr = ImGui::AcceptDragDropPayload("DragAndDropEntity")) {
                Runtime::EntityHandle handle{};

                // NOTE: due to misalignment we do memcpy (emscriptten catches the misalignment)
                // come back on this
                std::memcpy(&handle, payloadVoidPtr->Data, sizeof(handle));

                entity = handle;
                isDropped = true;
            }

            ImGui::EndDragDropTarget();
        }

        return isDropped;
    }

}
