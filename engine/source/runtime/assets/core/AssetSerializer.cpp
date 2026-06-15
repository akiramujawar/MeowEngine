//
// Created by Akira Mujawar on 05/03/26.
//

#include <AssetSerializer.hpp>
#include <AssetHeader.hpp>
#include <AssetType.hpp>
#include <AssetMetadata.hpp>

#include <Public/IO.hpp>
#include <MeowService.hpp>
#include <UUID.hpp>

#include <AssetManager.hpp>
#include <AssetRegistrySerializer.hpp>
#include <Project.hpp>


namespace {
    MeowEngine::Asset::AssetType GetAssetType(const std::string& extension) {
        if (extension == ".png" || extension == ".jpg") {
            return MeowEngine::Asset::AssetType::TEXTURE;
        }

        if (extension == ".obj") {
            return MeowEngine::Asset::AssetType::MESH;
        }

        return MeowEngine::Asset::AssetType::UNKNOWN;
    }

    void ImportTextureSetting(std::string& setting) {
        setting = "{}";
    }

    void ImportMeshSetting(std::string& setting) {
        setting = "{}";
    }

    std::string GetSettings(const MeowEngine::Asset::AssetType& type) {
        std::string setting;

        switch (type) {
            case MeowEngine::Asset::AssetType::TEXTURE:
                ImportTextureSetting(setting);
                break;
            case MeowEngine::Asset::AssetType::MESH:
                ImportMeshSetting(setting);
                break;
            case MeowEngine::Asset::AssetType::WORLD:
                break;
            case MeowEngine::Asset::AssetType::MATERIAL:
                break;
            default:
                break;
        }

        return setting;
    }
}

namespace MeowEngine::Asset {

    void AssetSerializer::Serialize(const std::string_view& importPath, const std::string_view& savePath) {
        const FileSystem::Path importFilePath(importPath);
        const Asset::AssetType type = GetAssetType(importFilePath.GetExtension().GetRawString());

        // only copy-paste
        if (type == Asset::AssetType::UNKNOWN) {
            FileSystem::FileSystem::Move(importFilePath, savePath);
            return;
        }

        // path to selected asset directory with new extension
        FileSystem::Path saveFilePath = FileSystem::Path(savePath) + importFilePath.GetName();
        saveFilePath.ReplaceExtension("meowdata");

        const uint64_t uuid = Core::UUID::GenerateUUID();
        const std::string setting = GetSettings(type);
        const std::vector<uint8_t> assetData = FileSystem::File::ReadAll(importPath);

        // set the header for the file
        Asset::AssetHeader header {uuid, static_cast<int>(type)};
        header.SettingIndicator = sizeof(Asset::AssetHeader);
        header.SettingSize = setting.size();
        header.DataIndicator = header.SettingIndicator + header.SettingSize;
        header.DataSize = assetData.size();

        // save to disk
        FileSystem::FileStream stream;
        stream.Open(saveFilePath, FileSystem::FileMode::WRITE);

        stream.Write(&header, sizeof(Asset::AssetHeader));
        stream.Write(setting.data(), header.SettingSize);
        stream.Write(assetData.data(), header.DataSize);

        stream.Flush();
        stream.Close();

        // MeowService().AssetManager.GetResolver().Add(uuid, Asset::AssetEntry{type,saveFilePath.CStr()});
        // Asset::Serializer::AssetRegistrySerializer::Serialize(
        //      MeowService().Project.Settings.GetAssetResolverPath(),
        //      MeowService().AssetManager.GetResolver()
        // );
    }

    bool AssetSerializer::Deserialize(const Path& path, AssetHeader& header) {
        FileSystem::FileStream stream;

        stream.Open(path.GetRawString().data(), FileSystem::FileMode::READ);

        // move indicator to asset data
        // (just by reading it auto seeks as header size is constant, we do it any way)
        stream.Read(&header, sizeof(Asset::AssetHeader));
        // stream.Seek(header.DataIndicator);

        // check for file validity
        if (strncmp(header.Magic, "MEOW", 4) != 0) {
            // throw std::runtime_error("Invalid Asset Resolver");
            std::string logMessage = "Invalid Asset: " + path.GetRawString();
            MeowEngine::Log("Asset Serializer", logMessage, LogType::ERROR);

            return false;
        }

        return true;
    }
}
