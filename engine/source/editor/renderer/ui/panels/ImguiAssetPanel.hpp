//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_IMGUIASSETPANEL_HPP
#define MEOWENGINE_IMGUIASSETPANEL_HPP


#include "ImguiAPI.hpp"

#include "string_view"
#include "string"

#include <Public/Core/Include.hpp>
#include <Public/IO/Forward.hpp>

#include "GLThumbnail.hpp"
#include "FolderCache.hpp"
#include "DirectoryAsset.hpp"

namespace MeowEngine::Rendering {
    struct RenderContext;
    class RenderResourceManager;
}

namespace MeowEngine::Messaging {
    class CommandQueue;
}

namespace MeowEngine::Editor {
    class ImguiCreateAssetPopupModal;
    class ImguiDeleteAssetPopupModal;
    class ImguiAssetRenamePopupModal;
    
    struct ImguiAssetPanel {
        ImguiAssetPanel();
        ~ImguiAssetPanel();

        void Draw(const Rendering::RenderContext& renderContext);

    private:
        void ShowTableHeaders(ImVec2 availableSpace);
        void ShowTableContents();
        void ShowLeftColumn(int flags);
        void ShowRightColumn(int flags);

        void ShowDirectory(const std::string& pathName, const Path& path, const Asset::FolderMap& map);

        void ShowSelectedDirectoryFiles();

        /**
         * We can move this into a thumbnail renderer or something similir
         * @param selectionData
         * @param path
         */
        void ShowThumbnail(const Asset::DirectoryAsset& assetFile);

        void ShowImportAssetPopupMenu();
        void ShowCreateAssetPopupMenu();
        void ShowAssetPanelPopupMenu();
        
    private:
        bool IsActive;
        ImGuiWindowFlags WindowFlags;
        const ImGuiTreeNodeFlags DefaultSelectableFlags;
        const ImGuiTreeNodeFlags DefaultSelectableNoListFlags;
        
        std::unique_ptr<ImguiCreateAssetPopupModal> ShowCreatePopupModal;
        std::unique_ptr<ImguiDeleteAssetPopupModal> ShowDeletePopupModal;
        std::unique_ptr<ImguiAssetRenamePopupModal> IsRenamingAsset;

        // From render context
        String SelectedFolderPath;
        String SelectedFilePath;

        Asset::FolderCache EngineFolderCache;
        Asset::FolderCache SandboxFolderCache;
        std::vector<Asset::DirectoryAsset> FilesInSelectedFolder;

        Messaging::CommandQueue* CommandQueue;
        Rendering::RenderResourceManager* ResourceManager;
    };
}


#endif //MEOWENGINE_IMGUIASSETPANEL_HPP
