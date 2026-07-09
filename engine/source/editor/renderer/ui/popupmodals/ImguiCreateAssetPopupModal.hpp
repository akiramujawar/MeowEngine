//
// Created by Akira Mujawar on 27/02/26.
//

#ifndef MEOWENGINE_IMGUICREATEASSETPOPUPMODAL_HPP
#define MEOWENGINE_IMGUICREATEASSETPOPUPMODAL_HPP

#include <Public/Core/Include.hpp>
#include <AssetType.hpp>

namespace MeowEngine::Editor {
    struct Selector;

    class ImguiCreateAssetPopupModal {
    public:
        ImguiCreateAssetPopupModal(const std::string_view& title, const Asset::AssetType& createType);
        ~ImguiCreateAssetPopupModal();
        
        /**
         * Returns true if popup needs to be closed
         * NOTE: Force close can be added if required otherwise self contained is good
         * @return
         */
        bool Draw(String selectedDirectoryPath);
        
    private:
        std::string TitleText;
        std::string InputText;
    
        Asset::AssetType AssetType;
    };
}


#endif //MEOWENGINE_IMGUICREATEASSETPOPUPMODAL_HPP
