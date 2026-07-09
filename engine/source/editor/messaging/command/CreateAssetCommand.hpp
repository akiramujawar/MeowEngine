//
// Created by Akira Mujawar on 09/07/26.
//

#ifndef MEOWENGINE_CREATEASSETCOMMAND_HPP
#define MEOWENGINE_CREATEASSETCOMMAND_HPP


#include <Public/Messaging/Include.hpp>
#include <Public/Core/Include.hpp>

#include "AssetType.hpp"

namespace MeowEngine::Messaging {
    class CreateAssetCommand  : public ICommand {
    public:
        CreateAssetCommand(const String& directoryPath, const String& assetName, Asset::AssetType type) {
            DirectoryPath = directoryPath;
            AssetName = assetName;
            Type = type;
        }

        void Execute(MessageInitData& context) override;

    private:
        String DirectoryPath;
        String AssetName;
        Asset::AssetType Type;
    };
}


#endif //MEOWENGINE_CREATEASSETCOMMAND_HPP