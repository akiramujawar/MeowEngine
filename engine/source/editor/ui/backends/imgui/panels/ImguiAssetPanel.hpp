//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_IMGUIASSETPANEL_HPP
#define MEOWENGINE_IMGUIASSETPANEL_HPP


#include "ImguiAPI.hpp"

#include "string_view"
#include "string"

#include "selection_data.hpp"
#include "opengl_thumbnail.hpp"

namespace MeowEngine::Core::IO::FileSystem {
    class Path;
}

namespace MeowEngine::Editor::UI {
    class ImguiCreateAssetPopupModal;
    
    struct ImguiAssetPanel {
        ImguiAssetPanel();
        ~ImguiAssetPanel();

        void Draw(MeowEngine::SelectionData& selectionData);

    private:
        void ShowTableHeaders();
        void ShowTableContents(MeowEngine::SelectionData& selectionData);
        void ShowDirectory(MeowEngine::SelectionData& selectionData,
                           const std::string& pathString,
                           const std::string& pathName);

        void ShowSelectedDirectoryFiles(SelectionData& selectionData);

        void ShowThumbnail(SelectionData& selectionData, const Core::IO::FileSystem::Path& path);
        void ShowCreateAssetPopupMenu();
    private:
        
        bool IsActive;
        ImGuiWindowFlags WindowFlags;
        const ImGuiTreeNodeFlags DefaultSelectableFlags;
        const ImGuiTreeNodeFlags DefaultSelectableNoListFlags;
        
        std::unique_ptr<Editor::UI::ImguiCreateAssetPopupModal> ShowCreatePopupModal;

        // TODO: Temp until we have loader system
        OpenGLThumbnail folderImage;
        OpenGLThumbnail unknownImage;
    };
}


#endif //MEOWENGINE_IMGUIASSETPANEL_HPP
