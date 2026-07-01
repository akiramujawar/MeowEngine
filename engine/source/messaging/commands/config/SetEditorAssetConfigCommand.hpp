//
// Created by Akira Mujawar on 01/07/26.
//

#ifndef MEOWENGINE_SETEDITORASSETCONFIG_HPP
#define MEOWENGINE_SETEDITORASSETCONFIG_HPP


#include <Public/Messaging/Include.hpp>
#include "AssetHandle.hpp"
#include "EditorAssetConfigType.hpp"

namespace MeowEngine::Messaging {
    class SetEditorAssetConfigCommand : public ICommand {
    public:
        SetEditorAssetConfigCommand(const Asset::AssetHandle& assetHandle, EditorAssetConfigType type) {
            AssetHandle = assetHandle;
            Type = type;
        }

        void Execute(MessageInitData& context) override;

    private:
        Asset::AssetHandle AssetHandle;
        EditorAssetConfigType Type;
    };
}


#endif //MEOWENGINE_SETEDITORASSETCONFIG_HPP