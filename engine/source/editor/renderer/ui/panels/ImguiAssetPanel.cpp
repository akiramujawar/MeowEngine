//
// Created by Akira Mujawar on 22/02/26.
//

#include "ImguiAssetPanel.hpp"

#include <imgui_internal.h>
#include "log.hpp"

#include <Public/IO/Include.hpp>
#include <MeowService.hpp>

#include "AssetLoader.hpp"
#include <ConfigManager.hpp>

#include "ImguiCreateAssetPopupModal.hpp"
#include "ImguiDeleteAssetPopupModal.hpp"
#include "ImguiAssetRenamePopupModal.hpp"

#include "ImguiAssetDragDrop.hpp"
#include "CreateAssetType.hpp"

#include <ImportFileCommand.hpp>
#include <RenderContext.hpp>
#include <RenderUIData.hpp>

#include <CommandQueue.hpp>
#include <SelectDirectoryPathCommand.hpp>
#include <SelectAssetPathCommand.hpp>
#include "LoadWorldCommand.hpp"

#include "RebuildAndSaveAssetRegistry.hpp"

#include "AssetManager.hpp"
#include "RenderResourceManager.hpp"

namespace MeowEngine::Editor {
    ImguiAssetPanel::ImguiAssetPanel()
        : WindowFlags(ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing)
        , DefaultSelectableFlags(
          ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth
        )
        , DefaultSelectableNoListFlags(
          DefaultSelectableFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen
        )
        , IsActive(false)
        , EngineFolderCache()
        , SandboxFolderCache() {
        PT_PROFILE_ALLOC("ImguiAssetPanel", sizeof(ImguiAssetPanel))
    }

    ImguiAssetPanel::~ImguiAssetPanel() {
        PT_PROFILE_FREE("ImguiAssetPanel")
    }

    void ImguiAssetPanel::Draw(const Rendering::RenderContext& renderContext) {
        SelectedFolderPath = renderContext.UIData->SelectedFolderPath.GetString();
        SelectedFilePath = renderContext.UIData->SelectedFilePath.GetString();
        FilesInSelectedFolder = renderContext.UIData->FilesInSelectedFolder;
        EngineFolderCache = renderContext.UIData->EngineDirectoryMap;
        SandboxFolderCache = renderContext.UIData->SandboxDirectoryMap;
        CommandQueue = renderContext.CommandQueue;
        ResourceManager = renderContext.ResourceManager;
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0, 0));
        
        ImGui::Begin("Assets", &IsActive, WindowFlags);
        {
            ImGui::PopStyleVar(3);
            ImGui::Dummy(ImVec2(0, 10));  // top padding
            ImGuiTableFlags flags = ImGuiTableFlags_Borders
                | ImGuiTableFlags_Resizable
                | ImGuiTableFlags_SizingStretchProp;
            
            
            auto availableSpace = ImGui::GetContentRegionAvail();
           
            if(ImGui::BeginTable("", 2, flags, availableSpace)) {
                ShowTableHeaders(availableSpace);
                ShowTableContents();
                
                ImGui::EndTable();
            }
            
            // draws the popup modal
            if(ShowCreatePopupModal && ShowCreatePopupModal->Draw(SelectedFolderPath)) {
                ShowCreatePopupModal.reset();
            }
            
            // draws the popup modal
            if(ShowDeletePopupModal && ShowDeletePopupModal->Draw()) {
                ShowDeletePopupModal.reset();
            }
    
            // draws the
            if(IsRenamingAsset && IsRenamingAsset->Draw()) {
                IsRenamingAsset.reset();
            }
            
            ImGui::End();
        }
        
    }
    
    void ImguiAssetPanel::ShowTableHeaders(ImVec2 availableSpace) {
        ImGui::TableSetupColumn("Directory");
        ImGui::TableSetupColumn("FolderView"); // folder view
    
        // draw header ------------------ start
        float headerHeight = ImGui::GetTextLineHeightWithSpacing() * 1.2f;
        ImGui::TableNextRow(ImGuiTableRowFlags_Headers, headerHeight);
    
        // draw "Directory" header
        ImGui::TableSetColumnIndex(0);
        ImGui::PushID(0); {
            const std::string& sideMenu = "Side Menu + ";
            if (ImGui::ArrowButtonEx(sideMenu.c_str(), ImGuiDir_Down, ImVec2(headerHeight, headerHeight))) {
                // TODO: implement modal poppup for this
                CommandQueue->Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::RebuildAndSaveAssetRegistry>()
                );
            }

            float textHeight = ImGui::GetTextLineHeight();
            float textOffset = (headerHeight - textHeight) * 0.5f - 3; // little manual okay sometimes :)

            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + textOffset);
            ImGui::TextUnformatted(ImGui::TableGetColumnName(0));

            ImGui::PopID();
        }
    
        // draw "FolderView" header
        ImGui::TableSetColumnIndex(1);
        ImGui::PushID(1);
        {
            // show import button (onclick: creates a popup window)
            const std::string& importButtonText = "Import + ";
            const ImVec2 importButtonSize(ImGui::CalcTextSize(importButtonText.c_str()).x, headerHeight);
            if (ImGui::Button(importButtonText.c_str(), importButtonSize)) {
                // display window for importing files.
                ImGui::OpenPopup("ShowImportAssetPopupMenu");
            }
    
            ImGui::SameLine();
    
            // show create button (onclick: shows a popup menu)
            const std::string& createButtonText = "Create + ";
            const ImVec2 createButtonSize(ImGui::CalcTextSize(createButtonText.c_str()).x, headerHeight);
            if (ImGui::Button(createButtonText.c_str(), createButtonSize)) {
                ImGui::OpenPopup("ShowCreateAssetPopupMenu");
            }

            ShowImportAssetPopupMenu();
            ShowCreateAssetPopupMenu();
            ImGui::PopID();
        }
    }
    
    void ImguiAssetPanel::ShowTableContents() {
        // folder view (tree)
        ImGui::TableNextRow(ImGuiTableRowFlags_None, ImGui::GetContentRegionAvail().y);
        constexpr auto flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar;

        ImGui::TableNextColumn() ;
        ShowLeftColumn(flags);

        ImGui::TableNextColumn();
        ShowRightColumn(flags);
    }

    void ImguiAssetPanel::ShowLeftColumn(int flags) {
        ImGui::BeginChild("##AssetsScrollableView", ImVec2(0,0), true, flags);
        // show open project assets
        {
            // auto projectPath = MeowService().Project.Paths.GetSandboxRootPath();
            // auto assetPath = projectPath + "assets";

            // MeowEngine::Log("Engine Path", assetPath.GetRawString());
            // ShowDirectory(assetPath.GetRawString(), "Project");
            if (ImGui::TreeNode("Sandbox")) {
                ShowDirectory("Assets", SandboxFolderCache.AssetPath, SandboxFolderCache.AssetsFolderMap);
                ShowDirectory("Shaders", SandboxFolderCache.ShaderPath, SandboxFolderCache.ShaderFolderMap);
                ShowDirectory("Source", SandboxFolderCache.SourcePath, SandboxFolderCache.SourceFolderMap);

                ImGui::TreePop();
            }
        }

        // show internal engine assets
        {
            // auto enginePath = MeowService().Project.Paths.GetEngineRootPath();
            // auto assetPath = enginePath + "engine/assets";
            //
            // MeowEngine::Log("Engine Path", enginePath.GetRawString());
            // ShowDirectory(assetPath.GetRawString(), "Engine");
            if (ImGui::TreeNode("Engine")) {
                ShowDirectory("Assets", EngineFolderCache.AssetPath, EngineFolderCache.AssetsFolderMap);
                ShowDirectory("Shaders", EngineFolderCache.ShaderPath, EngineFolderCache.ShaderFolderMap);
                ShowDirectory("Source", EngineFolderCache.SourcePath, EngineFolderCache.SourceFolderMap);

                ImGui::TreePop();
            }
        }
        ImGui::EndChild();
    }

    void ImguiAssetPanel::ShowRightColumn(int flags) {
        // thumbnail view (tiles)
        ImGui::BeginChild("##ThumbnailsScrollableView", ImVec2(0,0), true, flags);
        if(ImGui::BeginTable("DirectoryFiles", 4, ImGuiTableFlags_NoBordersInBody)) {
            ShowSelectedDirectoryFiles();
            ImGui::EndTable();
        }
        ImGui::EndChild();
    }

    // use the render ui data.
    // whenever a directory is created
    // create event to update the render ui data
    // then the new directory added will be queried in main thread and then update the render ui cache in extractor
    // for now we keep copy-pasting the data from main thread using extractor into render ui cache
    void ImguiAssetPanel::ShowDirectory(const std::string& pathName, const Path& path, const Asset::FolderMap& map) {
        // FileSystem::Path path { pathString };
        // FileSystem::Directory directory { path };
        auto iterator = map.find(path);
        if (iterator == map.end()) {
            return;
        }

        auto directoryFolder = iterator->second;

        ImGuiTreeNodeFlags flags = directoryFolder.Folders.empty() ? DefaultSelectableNoListFlags : DefaultSelectableFlags;
        flags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;

        // if the item is selected we add selected flag?
        if (path.GetRawString() == SelectedFolderPath.GetRawString()) {
            flags |= ImGuiTreeNodeFlags_Selected;
        }

        // draw the item and its child is exists
        bool isOpen = ImGui::TreeNodeEx(
            path.CStr(),
            flags,
            "%s",
            pathName.c_str()
        );

        // if item gets clicked with cache item
        if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
            // we treat folder as asset too, hence we update both directory path & asset path
            CommandQueue->Push(
                Messaging::ThreadType::MAIN,
                std::make_unique<Messaging::SelectDirectoryPathCommand>(String(path.GetRawString()))
            );

            CommandQueue->Push(
                Messaging::ThreadType::MAIN,
                std::make_unique<Messaging::SelectAssetPathCommand>(String(path.GetRawString()))
            );
        }
    
        ImguiAssetDragDrop::DropAssetOnFolder(path.GetRawString());

        if(!directoryFolder.Folders.empty() && isOpen){
            // show the child items in hierarchy
            for(auto& folder : directoryFolder.Folders) {
                ShowDirectory(folder.GetName().GetRawString(), folder, map);
            }

            ImGui::TreePop();
        }
    }

    void ImguiAssetPanel::ShowSelectedDirectoryFiles() {
        FileSystem::Path path { SelectedFolderPath.GetRawString() };
        FileSystem::Directory directory { path };
        std::vector<FileSystem::Path> assetPaths = directory.GetAll(false);

        for(const auto& file : FilesInSelectedFolder) {
            ImGui::TableNextColumn();
            ShowThumbnail(file);
        }
    }

    void ImguiAssetPanel::ShowThumbnail(const Asset::DirectoryAsset& assetFile) {
        // grab assets and create / get resource gpu thumbnails
        void* imagePtr = nullptr;
        switch (assetFile.Type) {
            case Asset::AssetType::PROJECT: {
                auto assetHandle = Asset::AssetHandle::Create(MeowService().ConfigManager.EditorConfig.ProjectIconGuid);
                if (MeowService().AssetManager.IsLoaded(assetHandle)) {
                    Rendering::TextureRenderHandle textureHandle(assetHandle);
                    imagePtr = ResourceManager->GetThumbnailResource(textureHandle).GetTextureID();
                }
                break;
            }
            case Asset::AssetType::FOLDER: {
                auto assetHandle = Asset::AssetHandle::Create(MeowService().ConfigManager.EditorConfig.FolderIconGuid);
                if (MeowService().AssetManager.IsLoaded(assetHandle)) {
                    Rendering::TextureRenderHandle textureHandle(assetHandle);
                    imagePtr = ResourceManager->GetThumbnailResource(textureHandle).GetTextureID();
                }
                break;
            }
            case Asset::AssetType::HPP: {
                auto assetHandle = Asset::AssetHandle::Create(MeowService().ConfigManager.EditorConfig.HppIconGuid);
                if (MeowService().AssetManager.IsLoaded(assetHandle)) {
                    Rendering::TextureRenderHandle textureHandle(assetHandle);
                    imagePtr = ResourceManager->GetThumbnailResource(textureHandle).GetTextureID();
                }
                break;
            }
            case Asset::AssetType::CPP: {
                auto assetHandle = Asset::AssetHandle::Create(MeowService().ConfigManager.EditorConfig.CppIconGuid);
                if (MeowService().AssetManager.IsLoaded(assetHandle)) {
                    Rendering::TextureRenderHandle textureHandle(assetHandle);
                    imagePtr = ResourceManager->GetThumbnailResource(textureHandle).GetTextureID();
                }
                break;
            }
            case Asset::AssetType::SHADER: {
                auto assetHandle = Asset::AssetHandle::Create(MeowService().ConfigManager.EditorConfig.ShaderIconGuid);
                if (MeowService().AssetManager.IsLoaded(assetHandle)) {
                    Rendering::TextureRenderHandle textureHandle(assetHandle);
                    imagePtr = ResourceManager->GetThumbnailResource(textureHandle).GetTextureID();
                }
                break;
            }
            case Asset::AssetType::TEXTURE: {
                auto assetHandle = Asset::AssetHandle::Create(MeowService().ConfigManager.EditorConfig.TextureIconGuid);
                if (MeowService().AssetManager.IsLoaded(assetHandle)) {
                    Rendering::TextureRenderHandle textureHandle(assetHandle);
                    imagePtr = ResourceManager->GetThumbnailResource(textureHandle).GetTextureID();
                }
                break;
            }
            case Asset::AssetType::MESH: {
                auto assetHandle = Asset::AssetHandle::Create(MeowService().ConfigManager.EditorConfig.MeshIconGuid);
                if (MeowService().AssetManager.IsLoaded(assetHandle)) {
                    Rendering::TextureRenderHandle textureHandle(assetHandle);
                    imagePtr = ResourceManager->GetThumbnailResource(textureHandle).GetTextureID();
                }
                break;
            }
            case Asset::AssetType::WORLD: {
                auto assetHandle = Asset::AssetHandle::Create(MeowService().ConfigManager.EditorConfig.WorldIconGuid);
                if (MeowService().AssetManager.IsLoaded(assetHandle)) {
                    Rendering::TextureRenderHandle textureHandle(assetHandle);
                    imagePtr = ResourceManager->GetThumbnailResource(textureHandle).GetTextureID();
                }
                break;
            }
            // case Asset::AssetType::MATERIAL:
            //     break;
            default:
            {
                auto assetHandle = Asset::AssetHandle::Create(MeowService().ConfigManager.EditorConfig.UnknownIconGuid);
                if (MeowService().AssetManager.IsLoaded(assetHandle)) {
                    Rendering::TextureRenderHandle textureHandle(assetHandle);
                    imagePtr = ResourceManager->GetThumbnailResource(textureHandle).GetTextureID();
                }
                break;
            }
        }

        
        ImGui::PushID(assetFile.AbsolutePath.CStr());
        
        ImVec2 thumbnailSize(100, 100);
        
        // show a button (hidden overlay)
        if(ImGui::InvisibleButton("button", thumbnailSize)) {
            CommandQueue->Push(
                Messaging::ThreadType::MAIN,
                std::make_unique<Messaging::SelectAssetPathCommand>(String(assetFile.AbsolutePath.GetRawString()))
            );
        }

        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
            MeowEngine::Log("Asset Selected: ", "Double Clicked");
            if (assetFile.Type == Asset::AssetType::WORLD) {
                CommandQueue->Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::LoadWorldCommand>(assetFile.FileHandle)
                );
            }
        }

        // prepare from the draw commands
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImVec2 min = ImGui::GetItemRectMin();
        ImVec2 max = ImGui::GetItemRectMax();
        ImVec2 center = ImVec2(
            (min.x + max.x) * 0.5f,
            (min.y + max.y) * 0.5f
        );
        ImVec2 imageSize(64, 64);
    
        // calculate asset icon size
        ImVec2 imageMinPosition(
            center.x - imageSize.x * 0.5f,
            max.y - ImGui::GetTextLineHeight() - imageSize.y
        );
    
        ImVec2 imageMaxPosition(
            center.x + imageSize.x * 0.5f,
            max.y - ImGui::GetTextLineHeight()
        );
    
        // calculate asset name text
        ImVec2 textSize = ImGui::CalcTextSize(assetFile.Name.CStr());
        ImVec2 textPosition = ImVec2(center.x - textSize.x * 0.5f, max.y - textSize.y - 3);
        
        // hover effect
        bool hovered = ImGui::IsItemHovered();
        
        ImU32 backgroundColor = hovered? IM_COL32(90, 90, 90, 255) : IM_COL32(0,0,0,0);
        // if selected keep it highlighted with blue color
        if(assetFile.AbsolutePath.GetStringView() == SelectedFilePath.GetRawString()) {
            backgroundColor = IM_COL32(0, 137, 209, 255);
        }
        
        // right click
        {
            if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                CommandQueue->Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::SelectAssetPathCommand>(assetFile.AbsolutePath.GetString())
                );
                
                ImGui::OpenPopup("ShowEditAssetMenu");
                MeowEngine::Log("Asset Right Clicked: ", assetFile.Name.CStr());
            }
        
            // show menu on right click
            if (ImGui::BeginPopup("ShowEditAssetMenu")) {
                if(ImGui::MenuItem("Delete")) {
                    ShowDeletePopupModal = std::make_unique<ImguiDeleteAssetPopupModal>(SelectedFilePath.GetRawString());
                }
                
                if(ImGui::MenuItem("Rename")) {
                    IsRenamingAsset = make_unique<ImguiAssetRenamePopupModal>(
                        min.x + 5,
                        textPosition.y,
                        max.x - min.x - 10,
                        ImGui::GetTextLineHeight(),
                        assetFile.AbsolutePath.GetRawString()
                    );
                }
                
                ImGui::EndPopup();
            }
        }
        
        // drag n drop
        ImguiAssetDragDrop::DragAsset(assetFile, assetFile.Name.CStr(), imagePtr);
        if (assetFile.IsFolder) {
            ImguiAssetDragDrop::DropAssetOnFolder(assetFile.AbsolutePath.GetRawString());
        }
        
        drawList->AddRectFilled(min, max, backgroundColor, 6.0f);
    
        // show asset icon
        drawList->AddImage(
            (ImTextureID)imagePtr,
            imageMinPosition,
            imageMaxPosition
        );

        // show asset name text (if a asset is being renamed, don't show for it)
        if(!(IsRenamingAsset && IsRenamingAsset->IsSamePath(assetFile.AbsolutePath.GetRawString()))) {
            drawList->AddText(textPosition, IM_COL32_WHITE, assetFile.Name.CStr());
        }

        ImGui::PopID();
    }

    void ImguiAssetPanel::ShowImportAssetPopupMenu() {
        if (ImGui::BeginPopup("ShowImportAssetPopupMenu")) {
            if(ImGui::MenuItem("Mesh")) {
                CommandQueue->Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::ImportFileCommand>(SelectedFolderPath.GetRawString(), Asset::AssetImportType::MESH)
                );
            }

            else if(ImGui::MenuItem("Texture")) {
                CommandQueue->Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::ImportFileCommand>(SelectedFolderPath.GetRawString(), Asset::AssetImportType::TEXTURE)
                );
            }
            else if(ImGui::MenuItem("Reimport World")) {
                CommandQueue->Push(
                    Messaging::ThreadType::MAIN,
                    std::make_unique<Messaging::ImportFileCommand>(SelectedFolderPath.GetRawString(), Asset::AssetImportType::WORLD)
                );
            }

            ImGui::EndPopup();
        }


    }

    void ImguiAssetPanel::ShowCreateAssetPopupMenu() {
        std::string titleText;
        AssetCreateType createType = AssetCreateType::NONE;
        
        // show popup menu for different types of items which can be created
        if (ImGui::BeginPopup("ShowCreateAssetPopupMenu")) {
            if(ImGui::MenuItem("Folder")) {
                FileSystem::Path directory(SelectedFolderPath.GetRawString());
                
                titleText = "Create folder?";
                createType = AssetCreateType::FOLDER;
            }
            
            if (ImGui::BeginMenu("Misc", "")) {  // 2nd param is for shortcut
                if(ImGui::MenuItem("World")) {
                    FileSystem::Path directory(SelectedFolderPath.GetRawString());
                    
                    titleText = "Create world?";
                    createType = AssetCreateType::WORLD;
                }
                ImGui::EndMenu();
            }
        
            ImGui::EndPopup();
        }
        
        
        // creates an object for popup to render. gets destroyed when popup is closed.
        if(createType != AssetCreateType::NONE) {
            ShowCreatePopupModal = make_unique<ImguiCreateAssetPopupModal>(titleText, createType);
        }
    }
}
