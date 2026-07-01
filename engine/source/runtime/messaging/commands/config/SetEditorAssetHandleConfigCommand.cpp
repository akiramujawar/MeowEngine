//
// Created by Akira Mujawar on 01/07/26.
//

#include "SetEditorAssetHandleConfigCommand.hpp"


#include "SetSandboxAssetHandleConfigCommand.hpp"

#include "ConfigManager.hpp"
#include "MeowService.hpp"
#include "MessageInitData.hpp"
#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::Messaging {

    void SetEditorAssetHandleConfigCommand::Execute(MessageInitData& context) {
        switch (Type) {
            case EditorAssetHandleType::PROJECT_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["ProjectIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetHandleType::FOLDER_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["FolderIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetHandleType::HPP_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["HppIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetHandleType::CPP_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["CppIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetHandleType::SHADER_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["ShaderIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetHandleType::MESH_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["MeshIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetHandleType::TEXTURE_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["TextureIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetHandleType::WORLD_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["WorldIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetHandleType::UNKNOWN_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["UnknownIconGuid"] = AssetHandle.GetUUID();
                break;
        }

        MeowService().ConfigManager.EditorConfig.SaveConfig();
    }

}
