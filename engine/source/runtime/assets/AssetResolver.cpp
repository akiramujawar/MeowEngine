//
// Created by Akira Mujawar on 05/03/26.
//

#include "AssetResolver.hpp"

#include <IO.hpp>
#include <ProjectSettings.hpp>

#include "AssetHeader.hpp"
#include "AssetType.hpp"

namespace MeowEngine::Runtime::Asset {
    void AssetResolver::Init() {
            MeowEngine::Log("AssetResolver", "Init");
            // projectName can be passed on while creating new project
            const std::string projectName = "example";
            const auto projectPath = FileSystem::Path(Settings::ProjectSettings::GetProjectPath());
            auto meowProject = projectPath + projectName;
            meowProject.ReplaceExtension(".meowproject");

            ResolverPath = meowProject.GetRawString();

            if (!meowProject.Exists()) {
                Create(meowProject);
            }

            Load();
        }

        /**
         * Creates a new .meowproject with header
         * NOTE: Currently we dont have a layer to create new project hence we give a hard name "example"
         * @param path
         */
        void AssetResolver::Create(const FileSystem::Path& path) {
            MeowEngine::Log("AssetResolver", "Creating Empty Project");

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

        /**
         * Loads asset resolver (.meowproject) & caches into asset resolver map
         */
        void AssetResolver::Load() {
            MeowEngine::Log("AssetResolver", "Load");

            FileSystem::FileStream stream;
            AssetHeader header;

            stream.Open(ResolverPath.data(), FileSystem::FileMode::READ);

            // move indicator to asset data
            // (just by reading it auto seeks as header size is constant, we do it any way)
            stream.Read(&header, sizeof(Asset::AssetHeader));
            // stream.Seek(header.DataIndicator);

            // check for file validity
            if (strncmp(header.Magic, "MEOW", 4) != 0) {
                throw std::runtime_error("Invalid asset");
            }

            // retrieve stores uuid & paths and push to resolverMap
            uint32_t assetCount(0);
            stream.Read(&assetCount, sizeof(uint32_t));

            for (auto i = 0; i < assetCount; i++) {
                uint64_t uuid;
                uint32_t pathSize;
                std::string path;

                stream.Read(&uuid, sizeof(uint64_t));
                stream.Read(&pathSize, sizeof(uint32_t));
                path.resize(pathSize, '\0');
                stream.Read(path.data(), pathSize);

                ResolverMap[uuid] = path;
            }
        }

        /**
         * Creates temp file, moves header & writes asset resolver map
         */
        void AssetResolver::Save() {
            MeowEngine::Log("AssetResolver", "Save");
            // techniques to achieve this
            // - memory mapped - best option
            // - json - simpler option - 4th best
            // - binary - 2nd best
            // - load entire file into memory then process - 3rd best
            // - read, parse move to next line - worst

            // temp file to write data on
            FileSystem::Path tempPath(ResolverPath);
            tempPath.ReplaceName("Temp");

            // stream and write the data (binary method)
            AssetHeader header;

            // - read header from existing resolver
            FileSystem::FileStream existingStream;
            existingStream.Open(ResolverPath.data(), FileSystem::FileMode::READ);
            existingStream.Read(&header, sizeof(AssetHeader));
            existingStream.Close();

            // - write header in temp resolver
            FileSystem::FileStream writeStream;
            writeStream.Open(tempPath, FileSystem::FileMode::WRITE);
            writeStream.Write(&header, sizeof(AssetHeader));

            // save the total counts followed by key-value
            uint32_t assetCount = ResolverMap.size();
            writeStream.Write(&assetCount, sizeof(uint32_t));

            for (const auto& [key, value] : ResolverMap) {
                uint32_t valueSize = value.size();

                // uuid, total size of path, path
                writeStream.Write(&key, sizeof(uint64_t));
                writeStream.Write(&valueSize, sizeof(uint32_t));
                writeStream.Write(value.data(), value.size());
            }

            writeStream.Flush();
            writeStream.Close();

            // replace temp with existing resolver file
            FileSystem::FileSystem::Replace(ResolverPath.data(), tempPath);
        }

        /**
         * Adds uuid to map & re-writes project asset resolver
         * @param uuid
         * @param path
         */
        void AssetResolver::Add(const uint64_t uuid, const std::string& path) {
            ResolverMap[uuid] = path;

            Save();
        }

        /**
         * Removes uuid from map & re-writes project asset resolver
         * @param uuid
         */
        void AssetResolver::Remove(const uint64_t uuid) {
            ResolverMap.erase(uuid);

            Save();
        }

        /**
         * TODO: Manual resolver, incase files where added / moved outside engine
         */
        void AssetResolver::Resolve() {
            MeowEngine::Log("AssetResolver", "Resolve: Not implemented", LogType::ERROR);
        }
}