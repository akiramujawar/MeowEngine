//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_IMGUIASSETPANEL_HPP
#define MEOWENGINE_IMGUIASSETPANEL_HPP


#include "ImguiAPI.hpp"

#include "string_view"
#include "string"

#include "Selector.hpp"
#include "opengl_thumbnail.hpp"

namespace MeowEngine::Core::IO::FileSystem {
    class Path;
}

namespace MeowEngine::Editor {
    class ImguiCreateAssetPopupModal;
    class ImguiDeleteAssetPopupModal;
    class ImguiAssetRenamePopupModal;
    
    struct ImguiAssetPanel {
        ImguiAssetPanel();
        ~ImguiAssetPanel();

        void Draw(Editor::Selector& selectionData);

    private:
        void ShowTableHeaders(Editor::Selector& selectionData);
        void ShowTableContents(Editor::Selector& selectionData);
        void ShowDirectory(Editor::Selector& selectionData,
                           const std::string& pathString,
                           const std::string& pathName);

        void ShowSelectedDirectoryFiles(Selector& selectionData);

        /**
         * We can move this into a thumbnail renderer or something similir
         * @param selectionData
         * @param path
         */
        void ShowThumbnail(Selector& selectionData, const Core::IO::FileSystem::Path& path);
        void ShowCreateAssetPopupMenu(Editor::Selector& selectionData);
        
    private:
        bool IsActive;
        ImGuiWindowFlags WindowFlags;
        const ImGuiTreeNodeFlags DefaultSelectableFlags;
        const ImGuiTreeNodeFlags DefaultSelectableNoListFlags;
        
        std::unique_ptr<ImguiCreateAssetPopupModal> ShowCreatePopupModal;
        std::unique_ptr<ImguiDeleteAssetPopupModal> ShowDeletePopupModal;
        std::unique_ptr<ImguiAssetRenamePopupModal> IsRenamingAsset;

        // TODO: Temp until we have loader system
        OpenGLThumbnail folderImage;
        OpenGLThumbnail unknownImage;
    };
}


#endif //MEOWENGINE_IMGUIASSETPANEL_HPP
