//
// Created by Akira Mujawar on 22/02/26.
//

#include "ImguiAssetPanel.hpp"
#include "log.hpp"

#include "IO.hpp"
#include "ProjectConfig.hpp"
#include "AssetLoader.hpp"
#include "ImguiCreateAssetPopupModal.hpp"
#include "ImguiDeleteAssetPopupModal.hpp"
#include "ImguiAssetRenamePopupModal.hpp"

#include "ImguiAssetDragDrop.hpp"
#include "CreateAssetType.hpp"

namespace MeowEngine::Editor::UI {
    ImguiAssetPanel::ImguiAssetPanel()
        : WindowFlags(ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing)
        , DefaultSelectableFlags(ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth)
        , DefaultSelectableNoListFlags(DefaultSelectableFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen)
        , IsActive(false)
        , folderImage(OpenGLThumbnail(assets::LoadBitmap("assets/icons/thumbnails/folder.png")))
        , unknownImage(OpenGLThumbnail(assets::LoadBitmap("assets/icons/thumbnails/unknown.png"))){
        PT_PROFILE_ALLOC("ImguiAssetPanel", sizeof(ImguiAssetPanel))

    }

    ImguiAssetPanel::~ImguiAssetPanel() {
        PT_PROFILE_FREE("ImguiAssetPanel")
    }

    void ImguiAssetPanel::Draw(MeowEngine::SelectionData& selectionData) {
        
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
                ShowTableHeaders(selectionData);
                ShowTableContents(selectionData);
                
                ImGui::EndTable();
            }
            
            // draws the popup modal
            if(ShowCreatePopupModal && ShowCreatePopupModal->Draw(selectionData)) {
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
    
    void ImguiAssetPanel::ShowTableHeaders(MeowEngine::SelectionData& selectionData) {
        ImGui::TableSetupColumn("Directory");
        ImGui::TableSetupColumn("FolderView"); // folder view
    
        // draw header ------------------ start
        float headerHeight = ImGui::GetTextLineHeightWithSpacing() * 1.2f;
        ImGui::TableNextRow(ImGuiTableRowFlags_Headers, headerHeight);
    
        // draw "Directory" header
        ImGui::TableSetColumnIndex(0);
        ImGui::PushID(0); {
            float textHeight = ImGui::GetTextLineHeight();
            float textOffset = (headerHeight - textHeight) * 0.5f;
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
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
                // NOTE: We create a event as creating a native window requires main thread.
                // TODO: ideally if dragging a file from outside and dropping is easier implement that
                // TODO: Create a way to handle & define the event types & data for code readability
                SDL_Event event;
                SDL_zero(event);
                event.type = SDL_USEREVENT;
                event.user.code = 4;
    
                SDL_PushEvent(&event);
            }
    
            ImGui::SameLine();
    
            // show create button (onclick: shows a popup menu)
            const std::string& createButtonText = "Create + ";
            const ImVec2 createButtonSize(ImGui::CalcTextSize(createButtonText.c_str()).x, headerHeight);
            if (ImGui::Button(createButtonText.c_str(), createButtonSize)) {
                ImGui::OpenPopup("ShowCreateAssetPopupMenu");
            }
    
            ShowCreateAssetPopupMenu(selectionData);
            ImGui::PopID();
        }
    }
    
    void ImguiAssetPanel::ShowTableContents(MeowEngine::SelectionData& selectionData) {
        // folder view (tree)
        ImGui::TableNextRow(ImGuiTableRowFlags_None, ImGui::GetContentRegionAvail().y);
        ImGui::TableNextColumn() ;
        
        auto flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar;
        ImGui::BeginChild("##AssetsScrollableView", ImVec2(0,0), true, flags);
        // show open project assets
        {
            auto projectPath = FileSystem::Path(Settings::ProjectSettings::GetProjectPath());
            auto assetPath = projectPath + "source";
        
            ShowDirectory(selectionData, assetPath.GetRawString(), "assets");
        }
    
        // show internal engine assets
        {
            auto enginePath = FileSystem::Path(Settings::ProjectSettings::GetEnginePath());
            auto assetPath = enginePath + "assets";
        
            ShowDirectory(selectionData, assetPath.GetRawString(), "engine");
        }
        ImGui::EndChild();
        
        // thumbnail view (tiles)
        ImGui::TableNextColumn();
        ImGui::BeginChild("##ThumbnailsScrollableView", ImVec2(0,0), true, flags);
        if(ImGui::BeginTable("DirectoryFiles", 4, ImGuiTableFlags_NoBordersInBody)) {
            ShowSelectedDirectoryFiles(selectionData);
            ImGui::EndTable();
        }
        ImGui::EndChild();
    }

    void ImguiAssetPanel::ShowDirectory(MeowEngine::SelectionData& selectionData,
                                               const std::string& pathString,
                                               const std::string& pathName) {
        FileSystem::Path path { pathString };
        FileSystem::Directory directory { path };
        std::vector<FileSystem::Path> directories = directory.GetDirectories(false);

        ImGuiTreeNodeFlags flags = directories.empty() ? DefaultSelectableNoListFlags : DefaultSelectableFlags;
        flags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;

        // if the item is selected we add selected flag?
        if (pathString == selectionData.SelectedDirectoryPath) {
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
            selectionData.SelectedDirectoryPath = path.GetRawString();
            selectionData.SelectedAssetPath = path.GetRawString();
    
            MeowEngine::Log("Directory Selected: ", path.GetName().GetRawString());
        }
    
        ImguiAssetDragDrop::DropAsset();

        if(!directories.empty() && isOpen){
            // show the child items in hierarchy
            for(auto& folder : directories) {
                ShowDirectory(selectionData, folder.GetRawString(), folder.GetName().GetRawString());
            }

            ImGui::TreePop();
        }
    }

    void ImguiAssetPanel::ShowSelectedDirectoryFiles(MeowEngine::SelectionData& selectionData) {
        FileSystem::Path path { selectionData.SelectedDirectoryPath };
        FileSystem::Directory directory { path };
        std::vector<FileSystem::Path> assetPaths = directory.GetAll(false);

        for(const auto& assetPath : assetPaths) {
            ImGui::TableNextColumn();
            ShowThumbnail(selectionData, assetPath);
        }
    }

    void ImguiAssetPanel::ShowThumbnail(SelectionData& selectionData,
                                        const FileSystem::Path& path) {
        FileSystem::Path name = path.GetName();
        
        // TODO: Once we have our full system ready to load/unload assets we update this properly
        void* imagePtr = path.GetExtension().GetStringView().empty()? folderImage.GetTextureID() : unknownImage.GetTextureID();
        
        ImGui::PushID(path.CStr());
        
        ImVec2 thumbnailSize(100, 100);
        
        // show a button (hidden overlay)
        if(ImGui::InvisibleButton("button", thumbnailSize)) {
            selectionData.SelectedAssetPath = path.GetRawString();
            MeowEngine::Log("Asset Selected", name.GetRawString());
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
        ImVec2 textSize = ImGui::CalcTextSize(name.CStr());
        ImVec2 textPosition = ImVec2(center.x - textSize.x * 0.5f, max.y - textSize.y - 10);
        
        // hover effect
        bool hovered = ImGui::IsItemHovered();
        
        ImU32 backgroundColor = hovered? IM_COL32(90, 90, 90, 255) : IM_COL32(0,0,0,0);
        if(path.GetStringView() == selectionData.SelectedAssetPath) {
            backgroundColor = IM_COL32(0, 137, 209, 255);
        }
        
        // right click
        {
            if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                selectionData.SelectedAssetPath = path.GetRawString();
                
                ImGui::OpenPopup("ShowEditAssetMenu");
                MeowEngine::Log("Asset Right Clicked: ", path.GetName().GetRawString());
            }
        
            // show menu on right click
            if (ImGui::BeginPopup("ShowEditAssetMenu")) {
                if(ImGui::MenuItem("Delete")) {
                    ShowDeletePopupModal = std::make_unique<ImguiDeleteAssetPopupModal>(selectionData.SelectedAssetPath);
                }
                
                if(ImGui::MenuItem("Rename")) {
                    IsRenamingAsset = make_unique<ImguiAssetRenamePopupModal>(
                        min.x + 5,
                        textPosition.y,
                        max.x - min.x - 10,
                        ImGui::GetTextLineHeight(),
                        path.GetRawString()
                    );
                }
                
                ImGui::EndPopup();
            }
        }
        
        // drag n drop
        ImguiAssetDragDrop::DragAsset(path.GetRawString(), path.GetName().GetRawString(), imagePtr);
        ImguiAssetDragDrop::DropAsset();
        
        drawList->AddRectFilled(min, max, backgroundColor, 6.0f);
    
        // show asset icon
        drawList->AddImage(
            (ImTextureID)imagePtr,
            imageMinPosition,
            imageMaxPosition
        );

        // show asset name text (if a asset is being renamed, don't show for it)
        if(!(IsRenamingAsset && IsRenamingAsset->IsSamePath(path.GetRawString()))) {
            drawList->AddText(textPosition, IM_COL32_WHITE, name.CStr());
        }

        ImGui::PopID();
    }

    void ImguiAssetPanel::ShowCreateAssetPopupMenu(MeowEngine::SelectionData& selectionData) {
        std::string titleText;
        AssetCreateType createType = AssetCreateType::NONE;
        
        // show popup menu for different types of items which can be created
        if (ImGui::BeginPopup("ShowCreateAssetPopupMenu")) {
            if(ImGui::MenuItem("Folder")) {
                FileSystem::Path directory(selectionData.SelectedDirectoryPath);
                
                titleText = "Create folder?";
                createType = AssetCreateType::FOLDER;
            }
            
            if (ImGui::BeginMenu("Misc", "")) {  // 2nd param is for shortcut
                if(ImGui::MenuItem("World")) {
                    FileSystem::Path directory(selectionData.SelectedDirectoryPath);
                    
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