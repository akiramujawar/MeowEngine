//
// Created by Akira Mujawar on 02/03/26.
//

#ifndef MEOWENGINE_IMGUIASSETRENAMEPOPUPMODAL_HPP
#define MEOWENGINE_IMGUIASSETRENAMEPOPUPMODAL_HPP

#include "string"

namespace MeowEngine::Editor::UI {
    class ImguiAssetRenamePopupModal {
    public:
        ImguiAssetRenamePopupModal(float x, float y, float width, float height, const std::string_view& assetPath);
        ~ImguiAssetRenamePopupModal();
        
        bool IsSamePath(const std::string& assetPath);
        bool Draw();
        
    private:
        float X, Y;
        float Width, Height;
        
        std::string AssetPath;
        std::string RenameTextBuffer;
    };
}


#endif //MEOWENGINE_IMGUIASSETRENAMEPOPUPMODAL_HPP
