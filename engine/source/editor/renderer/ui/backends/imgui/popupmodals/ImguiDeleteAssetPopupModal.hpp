//
// Created by Akira Mujawar on 02/03/26.
//

#ifndef MEOWENGINE_IMGUIDELETEASSETPOPUPMODAL_HPP
#define MEOWENGINE_IMGUIDELETEASSETPOPUPMODAL_HPP

#include "string"

namespace MeowEngine {
    struct SelectionData;
}

namespace MeowEngine::Editor::UI {
    class ImguiDeleteAssetPopupModal {
    public:
        ImguiDeleteAssetPopupModal(const std::string_view& assetPath);
        ~ImguiDeleteAssetPopupModal();
        
        /**
         * Returns true if popup needs to be closed
         * TODO: When file is deleted we need to update the selection data or it might create bugs
         * @return
         */
        bool Draw();
        
    private:
        std::string TitleText;
        std::string AssetPath;
    };
}


#endif //MEOWENGINE_IMGUIDELETEASSETPOPUPMODAL_HPP
