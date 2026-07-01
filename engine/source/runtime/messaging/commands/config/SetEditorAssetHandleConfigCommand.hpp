//
// Created by Akira Mujawar on 01/07/26.
//

#ifndef MEOWENGINE_SETEDITORASSETCONFIG_HPP
#define MEOWENGINE_SETEDITORASSETCONFIG_HPP


#include <Public/Messaging/Include.hpp>
#include "AssetHandle.hpp"
#include "EditorAssetHandleType.hpp"

namespace MeowEngine::Messaging {
    class SetEditorAssetHandleConfigCommand : public ICommand {
    public:
        SetEditorAssetHandleConfigCommand(const Asset::AssetHandle& assetHandle, EditorAssetHandleType type) {
            AssetHandle = assetHandle;
            Type = type;
        }

        void Execute(MessageInitData& context) override;

    private:
        Asset::AssetHandle AssetHandle;
        EditorAssetHandleType Type;
    };
}


#endif //MEOWENGINE_SETEDITORASSETCONFIG_HPP