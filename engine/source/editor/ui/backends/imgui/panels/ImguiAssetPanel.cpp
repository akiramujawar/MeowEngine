//
// Created by Akira Mujawar on 22/02/26.
//

#include "ImguiAssetPanel.hpp"
#include "log.hpp"

#include "IO.hpp"
#include "ProjectConfig.hpp"
#include "AssetLoader.hpp"


namespace MeowEngine::Runtime {
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

        ImGui::Begin("Assets", &IsActive, WindowFlags);
        {
            if(ImGui::Button("Demo")) {
                MeowEngine::Log("Button", "Clicked");

                FileSystem::Path AssetPath { "assets/test" };
                FileSystem::Directory Folder { AssetPath };
//                FileSystem::Directory Directory(); // why is this allowed. investigate

                if(Folder.Exists()) {
                    MeowEngine::Log("Exists", AssetPath.Exists());
                    MeowEngine::Log("GetParent", AssetPath.GetParent().GetRawString());
                    MeowEngine::Log("GetName", AssetPath.GetName().GetRawString());
                    MeowEngine::Log("GetExtension", AssetPath.GetExtension().GetRawString());

                    MeowEngine::Log("IsAbsolute", AssetPath.IsAbsolute());
                    MeowEngine::Log("IsRelative", AssetPath.IsRelative());

                    for(auto file : Folder.GetFiles(false)) {
                        MeowEngine::Log("Files", file.CStr());
                    }

                    for(auto file : Folder.GetDirectories(false)) {
                        MeowEngine::Log("Folders", file.CStr());
                    }

//                    FileSystem::FileSystem::Remove(AssetPath);
                }
                else {
                    FileSystem::FileSystem::CreateDirectory(AssetPath);
                }

            }

            ImGuiTableFlags flags;
            flags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingStretchProp;
            auto availableSize = ImGui::GetContentRegionAvail();

            if(ImGui::BeginTable("", 2, flags, ImGui::GetContentRegionAvail())) {
                ImGui::TableSetupColumn("Project");
                ImGui::TableSetupColumn("");

                ImGui::TableHeadersRow();

                // Folder View
//                ImGui::TableNextRow(ImGuiTableRowFlags_None, 20);
                ImGui::TableNextRow(ImGuiTableRowFlags_None, ImGui::GetContentRegionAvail().y);
                ImGui::TableNextColumn() ;

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

                // thumbnail view
                ImGui::TableNextColumn();
                if(ImGui::BeginTable("DirectoryFiles", 4, ImGuiTableFlags_NoBordersInBody)) {
                    ShowSelectedDirectoryFiles(selectionData);
                    ImGui::EndTable();
                }

                ImGui::EndTable();
            }

            ImGui::End();
        }
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
        
        ImVec2 size(100, 100);
        ImGui::PushID(path.CStr());

        // show a button (hidden overlay)
        if(ImGui::InvisibleButton("button", size)) {
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

        // hover effect
        bool hovered = ImGui::IsItemHovered();
        ImU32 backgroundColor = hovered? IM_COL32(90, 90, 90, 255) : IM_COL32(0,0,0,0);
        if(path.GetStringView() == selectionData.SelectedAssetPath) {
            backgroundColor = IM_COL32(0, 137, 209, 255);
        }
        
        drawList->AddRectFilled(min, max, backgroundColor, 6.0f);

        // calculate text
        ImVec2 textSize = ImGui::CalcTextSize(name.CStr());
        ImVec2 textPosition = ImVec2(center.x - textSize.x * 0.5f, max.y - textSize.y - 10);

        // calculate image
        ImVec2 imageSize(64, 64);
        ImVec2 imageMinPosition(
            center.x - imageSize.x * 0.5f,
            textPosition.y - imageSize.y
        );

        ImVec2 imageMaxPosition(
            center.x + imageSize.x * 0.5f,
            textPosition.y
        );

        // TODO: Once we have our full system ready to load/unload assets we update this properly
        // draw
        void* imageData = path.GetExtension().GetStringView().empty()? folderImage.GetTextureID() : unknownImage.GetTextureID();
        drawList->AddImage(
            (ImTextureID)imageData,
            imageMinPosition,
            imageMaxPosition
        );

        drawList->AddText(textPosition, IM_COL32_WHITE, name.CStr());

        ImGui::PopID();
    }
}