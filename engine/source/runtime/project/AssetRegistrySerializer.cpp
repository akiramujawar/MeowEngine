//
// Created by Akira Mujawar on 11/03/26.
//

#include <AssetRegistrySerializer.hpp>

#include <IO.hpp>
#include <AssetRegistry.hpp>
#include <AssetHeader.hpp>
#include <AssetType.hpp>

namespace MeowEngine::Runtime::Asset::Serializer {

    void AssetRegistrySerializer::Serialize(const FileSystem::Path& resolverPath, const AssetRegistry& resolverAsset) {
        MeowEngine::Log("AssetResolverSerializer", "Serialize");
        // techniques to achieve this
        // - memory mapped - best option
        // - json - simpler option - 4th best
        // - binary - 2nd best
        // - load entire file into memory then process - 3rd best
        // - read, parse move to next line - worst

        if (!resolverPath.Exists()) {
            Create(resolverPath);
        }

        // temp file to write data on
        FileSystem::Path tempPath(resolverPath);
        tempPath.ReplaceName("Temp");

        // stream and write the data (binary method)
        AssetHeader header;

        // - read header from existing resolver
        FileSystem::FileStream existingStream;
        existingStream.Open(resolverPath.GetRawString().data(), FileSystem::FileMode::READ);
        existingStream.Read(&header, sizeof(AssetHeader));
        existingStream.Close();

        // - write header in temp resolver
        FileSystem::FileStream writeStream;
        writeStream.Open(tempPath, FileSystem::FileMode::WRITE);
        writeStream.Write(&header, sizeof(AssetHeader));

        // save the total counts followed by key-value
        uint32_t assetCount = resolverAsset.ResolverMap.size();
        writeStream.Write(&assetCount, sizeof(uint32_t));

        for (const auto& [key, value] : resolverAsset.ResolverMap) {
            uint32_t entrySize = sizeof(value);

            // uuid, total size of path, path
            writeStream.Write(&key, sizeof(uint64_t));
            writeStream.Write(&entrySize, sizeof(uint32_t));
            writeStream.Write(&value, entrySize);
        }

        writeStream.Flush();
        writeStream.Close();

        // replace temp with existing resolver file
        FileSystem::FileSystem::Replace(resolverPath.GetRawString().data(), tempPath);
    }

    void AssetRegistrySerializer::Deserialize(const FileSystem::Path& resolverPath, AssetRegistry& resolverAsset) {
        if (!resolverPath.Exists()) {
            Create(resolverPath);
        }

        MeowEngine::Log("AssetResolverSerializer", "Deserialize");

        FileSystem::FileStream stream;
        AssetHeader header;

        stream.Open(resolverPath.GetRawString().data(), FileSystem::FileMode::READ);

        // move indicator to asset data
        // (just by reading it auto seeks as header size is constant, we do it any way)
        stream.Read(&header, sizeof(Asset::AssetHeader));
        // stream.Seek(header.DataIndicator);

        // check for file validity
        if (strncmp(header.Magic, "MEOW", 4) != 0) {
            throw std::runtime_error("Invalid Asset Resolver");
        }

        // retrieve stores uuid & paths and push to resolverMap
        uint32_t assetCount(0);
        stream.Read(&assetCount, sizeof(uint32_t));

        for (auto i = 0; i < assetCount; i++) {
            uint64_t uuid;
            uint32_t entrySize;
            AssetEntry entry;

            stream.Read(&uuid, sizeof(uint64_t));
            stream.Read(&entrySize, sizeof(uint32_t));
            stream.Read(&entry, entrySize);

            resolverAsset.Add(uuid, entry);
        }
    }

    void AssetRegistrySerializer::Create(const FileSystem::Path& path) {
        MeowEngine::Log("AssetResolverSerializer", {"Creating Empty Resolver", path.GetRawString()});

        AssetHeader header {0, static_cast<int>(Asset::AssetType::PROJECT)};
        header.SettingIndicator = sizeof(Asset::AssetHeader);
        header.SettingSize = 0;
        header.DataIndicator = header.SettingIndicator + header.SettingSize;
        header.DataSize = 0;

        FileSystem::FileStream stream;
        stream.Open(path, FileSystem::FileMode::WRITE);

        stream.Write(&header, sizeof(Asset::AssetHeader));

        stream.Flush();
        stream.Close();
    }

}