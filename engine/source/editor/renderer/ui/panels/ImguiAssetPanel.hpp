//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_IMGUIASSETPANEL_HPP
#define MEOWENGINE_IMGUIASSETPANEL_HPP


#include "ImguiAPI.hpp"

#include "string_view"
#include "string"

#include <Public/Core.hpp>
#include "opengl_thumbnail.hpp"

#include <Public/IO/Forward.hpp>

namespace MeowEngine::Rendering {
    struct RenderContext;
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
        void ShowTableHeaders();
        void ShowTableContents();
        void ShowDirectory(const std::string& pathString, const std::string& pathName);

        void ShowSelectedDirectoryFiles();

        /**
         * We can move this into a thumbnail renderer or something similir
         * @param selectionData
         * @param path
         */
        void ShowThumbnail(const FileSystem::Path& path);
        void ShowCreateAssetPopupMenu();
        
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

        // From render context
        String SelectedDirectoryPath;
        String SelectedAssetPath;
        Messaging::CommandQueue* CommandQueue;
    };
}


#endif //MEOWENGINE_IMGUIASSETPANEL_HPP
