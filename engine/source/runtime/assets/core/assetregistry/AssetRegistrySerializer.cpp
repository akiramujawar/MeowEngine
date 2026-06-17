//
// Created by Akira Mujawar on 11/03/26.
//

#include <AssetRegistrySerializer.hpp>

#include <Public/Core/Include.hpp>
#include <Public/IO/Include.hpp>

#include "AssetSerializer.hpp"
#include <AssetRegistry.hpp>
#include <AssetHeader.hpp>
#include <AssetType.hpp>


namespace MeowEngine::Asset {
    bool AssetRegistrySerializer::Serialize(const Path& path, const AssetRegistry& resolverAsset) {
        MeowEngine::Log("AssetResolverSerializer", "Serialize");
        // techniques to achieve this
        // - memory mapped - best option
        // - json - simpler option - 4th best
        // - binary - 2nd best
        // - load entire file into memory then process - 3rd best
        // - read, parse move to next line - worst

        // read existing header
        auto readSerializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);
        AssetHeader header;
        AssetSerializer::ReadHeader(readSerializer, header);
        AssetSerializer::CloseSerializer(readSerializer);

        auto tempPath = path;
        tempPath.ReplaceExtension("meowtemp");

        auto writeSerializer = AssetSerializer::OpenSerializer(tempPath, FileSystem::FileMode::WRITE);
        AssetSerializer::WriteHeader(writeSerializer, header);

        // save the total counts followed by key-value
        uint32_t assetCount = resolverAsset.GetSize();
        writeSerializer.WriteUInt32(assetCount);

        const auto& map = resolverAsset.GetMap();
        for (auto iterator = map.begin(); iterator != map.end(); ++iterator) {
            auto test = iterator->first;
            auto test1 = iterator->first.GetUUID();
            auto test2 = iterator->second;

            writeSerializer.WriteUInt64(iterator->first.GetUUID());
            AssetSerializer::WriteMetadata(writeSerializer, iterator->second);
        }

        AssetSerializer::CloseSerializer(writeSerializer);

        if (!FileSystem::FileSystem::Replace(path, tempPath)) {
            FileSystem::FileSystem::Remove(tempPath);

            return false;
        }

        return true;
    }

    bool AssetRegistrySerializer::Deserialize(const Path& path, AssetRegistry& resolverAsset) {
        // if doesn't exist's, create the asset file
        if (!path.Exists()) {
            Create(path);
        }

        auto serializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);

        AssetHeader header;
        bool isValidAsset = AssetSerializer::ReadHeader(serializer, header);

        if (!isValidAsset) {
            return false;
        }

        // retrieve stores uuid & paths and push to resolverMap
        uint32_t assetCount = serializer.ReadUInt32();
        for (auto i = 0; i < assetCount; i++) {
            uint64_t uuid = serializer.ReadUInt64();

            AssetMetadata metadata;
            AssetSerializer::ReadMetadata(serializer, metadata);

            resolverAsset.Add(AssetHandle::Create(uuid), metadata);
        }

        AssetSerializer::CloseSerializer(serializer);

        return true;
    }

    void AssetRegistrySerializer::Create(const Path& path) {
        MeowEngine::Log("AssetResolverSerializer", {"Creating Empty Resolver", path.GetRawString()});

        auto serializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::WRITE);

        AssetHeader header {0, static_cast<int>(Asset::AssetType::PROJECT)};
        header.SettingIndicator = sizeof(Asset::AssetHeader);
        header.SettingSize = 0;
        header.DataIndicator = header.SettingIndicator + header.SettingSize;
        header.DataSize = 0;

        AssetSerializer::WriteHeader(serializer, header);
        serializer.WriteUInt32(0);

        AssetSerializer::CloseSerializer(serializer);
    }

}