//
// Created by Akira Mujawar on 27/02/26.
//

#ifndef MEOWENGINE_IMGUICREATEASSETPOPUPMODAL_HPP
#define MEOWENGINE_IMGUICREATEASSETPOPUPMODAL_HPP

#include "string"

namespace MeowEngine::Editor::UI {
    class ImguiCreateAssetPopupModal {
    public:
        ImguiCreateAssetPopupModal(const std::string& createType);
        ~ImguiCreateAssetPopupModal();
        
        /**
         * Returns true if popup needs to be closed
         * NOTE: Force close can be added if required otherwise self contained is good
         * @return
         */
        bool Draw();
        
    private:
        std::string CreateTypeString;
        std::string TitleString;
        
    public:
        static void ShowMenuItem(const std::string& name, std::string& createType);
    };
}


#endif //MEOWENGINE_IMGUICREATEASSETPOPUPMODAL_HPP
