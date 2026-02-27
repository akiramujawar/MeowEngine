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
        , thumbnail(OpenGLThumbnail(assets::LoadBitmap("assets/icons/thumbnails/folder.png"))){
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
            flags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Hideable;
            if(ImGui::BeginTable("", 2, flags)) {
                ImGui::TableSetupColumn("Project");
                ImGui::TableSetupColumn("");

                ImGui::TableHeadersRow();

                // Folder View
                ImGui::TableNextRow(ImGuiTableRowFlags_None, 20);
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

                // Thumbnail View
                ImGui::TableNextColumn();
                if(ImGui::BeginTable("test", 4, ImGuiTableFlags_NoBordersInBody)) {
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
//        if (!pIsItemClicked && ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
        if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
            MeowEngine::Log("Directory Selected: ", path.GetName().GetRawString());
            selectionData.SelectedDirectoryPath = path.GetRawString();
//            pIsItemClicked = true;
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

            // TODO: Once we have our full system ready to load/unload assets we update this properly
//            auto thumbnailTexture = assets::LoadBitmap("assets/icons/thumbnails/folder.png");
//            auto thumbnailRenderer = OpenGLThumbnail(thumbnailTexture);
            thumbnail.Bind();
            float width = thumbnail.GetWidth();
            float height = thumbnail.GetHeight();
//            float width = 1;
//            float height = 1;

//            ImVec2 size = ImVec2(32.0f, 32.0f);                         // Size of the image we want to make visible
//            ImVec2 uv0 = ImVec2(0.0f, 0.0f);                            // UV coordinates for lower-left
//            ImVec2 uv1 = ImVec2(32.0f / width, 32.0f / height);    // UV coordinates for (32,32) in our texture
//            ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);             // Black background
//            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);           // No tint
//
//            ImGui::Image((ImTextureID)thumbnailRenderer.GetTextureID(), size, uv0, uv1, bg_col, tint_col);
            ImGui::Image((ImTextureID)thumbnail.GetTextureID(), ImVec2(64,64));
            ImGui::Text("%s", assetPath.GetName().CStr());

        }
    }
}