//
// Created by Akira Mujawar on 22/02/26.
//

#include "ImguiEditorSettingPanel.hpp"

#include "log.hpp"
#include "MeowService.hpp"
#include "CommandQueue.hpp"
#include "ImguiInputExtension.hpp"
#include "SetEditorAssetHandleConfigCommand.hpp"

namespace MeowEngine::Editor {
    ImguiEditorSettingPanel::ImguiEditorSettingPanel()
        : WindowFlags(ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing), IsActive(false) {
        PT_PROFILE_ALLOC("ImguiEditorSettingPanel", sizeof(ImguiEditorSettingPanel))
    }

    ImguiEditorSettingPanel::~ImguiEditorSettingPanel() {
        PT_PROFILE_FREE("ImguiEditorSettingPanel")
    }

    void ImguiEditorSettingPanel::Draw() {
        ImGui::Begin("Editor Settings", &IsActive, WindowFlags);
        {
            Asset::AssetHandle projectIconHandle = Asset::AssetHandle::CreateInvalid();
            ImGuiInputExtension::DragAndDropAssetInput("Project Icon", projectIconHandle);
            if (projectIconHandle.GetIsValid()) {
                MeowService().CommandQueue.Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SetEditorAssetHandleConfigCommand>(
                        projectIconHandle,
                        Messaging::EditorAssetHandleType::PROJECT_ICON
                    )
                );
            }

            Asset::AssetHandle folderIconHandle = Asset::AssetHandle::CreateInvalid();
            ImGuiInputExtension::DragAndDropAssetInput("Folder Icon", folderIconHandle);
            if (folderIconHandle.GetIsValid()) {
                MeowService().CommandQueue.Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SetEditorAssetHandleConfigCommand>(
                        folderIconHandle,
                        Messaging::EditorAssetHandleType::FOLDER_ICON
                    )
                );
            }

            Asset::AssetHandle hppIconHandle = Asset::AssetHandle::CreateInvalid();
            ImGuiInputExtension::DragAndDropAssetInput("Hpp Icon", hppIconHandle);
            if (hppIconHandle.GetIsValid()) {
                MeowService().CommandQueue.Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SetEditorAssetHandleConfigCommand>(
                        hppIconHandle,
                        Messaging::EditorAssetHandleType::HPP_ICON
                    )
                );
            }

            Asset::AssetHandle cppIconHandle = Asset::AssetHandle::CreateInvalid();
            ImGuiInputExtension::DragAndDropAssetInput("Cpp Icon", cppIconHandle);
            if (cppIconHandle.GetIsValid()) {
                MeowService().CommandQueue.Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SetEditorAssetHandleConfigCommand>(
                        cppIconHandle,
                        Messaging::EditorAssetHandleType::CPP_ICON
                    )
                );
            }

            Asset::AssetHandle shaderIconHandle = Asset::AssetHandle::CreateInvalid();
            ImGuiInputExtension::DragAndDropAssetInput("Shader Icon", shaderIconHandle);
            if (shaderIconHandle.GetIsValid()) {
                MeowService().CommandQueue.Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SetEditorAssetHandleConfigCommand>(
                        shaderIconHandle,
                        Messaging::EditorAssetHandleType::SHADER_ICON
                    )
                );
            }

            Asset::AssetHandle worldIconHandle = Asset::AssetHandle::CreateInvalid();
            ImGuiInputExtension::DragAndDropAssetInput("World Icon", worldIconHandle);
            if (worldIconHandle.GetIsValid()) {
                MeowService().CommandQueue.Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SetEditorAssetHandleConfigCommand>(
                        worldIconHandle,
                        Messaging::EditorAssetHandleType::WORLD_ICON
                    )
                );
            }

            Asset::AssetHandle meshIconHandle = Asset::AssetHandle::CreateInvalid();
            ImGuiInputExtension::DragAndDropAssetInput("Mesh Icon", meshIconHandle);
            if (meshIconHandle.GetIsValid()) {
                MeowService().CommandQueue.Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SetEditorAssetHandleConfigCommand>(
                        meshIconHandle,
                        Messaging::EditorAssetHandleType::MESH_ICON
                    )
                );
            }

            Asset::AssetHandle textureIconHandle = Asset::AssetHandle::CreateInvalid();
            ImGuiInputExtension::DragAndDropAssetInput("Texture Icon", textureIconHandle);
            if (textureIconHandle.GetIsValid()) {
                MeowService().CommandQueue.Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SetEditorAssetHandleConfigCommand>(
                        textureIconHandle,
                        Messaging::EditorAssetHandleType::TEXTURE_ICON
                    )
                );
            }

            Asset::AssetHandle unknownIconHandle = Asset::AssetHandle::CreateInvalid();
            ImGuiInputExtension::DragAndDropAssetInput("Unknown Icon", unknownIconHandle);
            if (unknownIconHandle.GetIsValid()) {
                MeowService().CommandQueue.Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SetEditorAssetHandleConfigCommand>(
                        unknownIconHandle,
                        Messaging::EditorAssetHandleType::UNKNOWN_ICON
                    )
                );
            }


            ImGui::End();
        }
    }
}