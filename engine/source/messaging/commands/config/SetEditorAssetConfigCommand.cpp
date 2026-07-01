//
// Created by Akira Mujawar on 01/07/26.
//

#include "SetEditorAssetConfigCommand.hpp"


#include "SetSandboxConfig.hpp"

#include "ConfigManager.hpp"
#include "MeowService.hpp"
#include "MessageInitData.hpp"
#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::Messaging {

    void SetEditorAssetConfigCommand::Execute(MessageInitData& context) {
        switch (Type) {
            case EditorAssetConfigType::PROJECT_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["ProjectIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetConfigType::FOLDER_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["FolderIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetConfigType::HPP_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["HppIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetConfigType::CPP_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["CppIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetConfigType::SHADER_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["ShaderIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetConfigType::MESH_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["MeshIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetConfigType::TEXTURE_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["TextureIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetConfigType::WORLD_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["WorldIconGuid"] = AssetHandle.GetUUID();
                break;
            case EditorAssetConfigType::UNKNOWN_ICON:
                MeowService().ConfigManager.EditorConfig.GetConfig()["UnknownIconGuid"] = AssetHandle.GetUUID();
                break;
        }

        MeowService().ConfigManager.EditorConfig.SaveConfig();
    }

}
