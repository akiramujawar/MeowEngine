//
// Created by Akira Mujawar on 25/06/26.
//

#include "ShaderBuilder.hpp"

#include "Public/Core/Include.hpp"
#include "MeowService.hpp"

#include "ConfigManager.hpp"
#include "ShaderImporter.hpp"

namespace MeowEngine::Asset {
    void ShaderBuilder::CreateShaderAssets() {
        const auto engineRootPath = MeowService().ConfigManager.Paths.GetEngineRootPath();
        const auto engineShaderRawPath = engineRootPath + "engine/shaders";
        const auto engineShaderCachePath = engineRootPath + "engine/shaders/compiled";

        Create(engineShaderRawPath, engineShaderCachePath);

        const auto sandboxRootPath = MeowService().ConfigManager.Paths.GetSandboxRootPath();
        const auto sandboxShaderRawPath = sandboxRootPath + "shaders";
        const auto sandboxShaderCachePath = sandboxRootPath + "shaders/compiled";

        Create(sandboxShaderRawPath, sandboxShaderCachePath);
    }

    void ShaderBuilder::Create(const Path& rawPath, const Path& cachePath) {
        // if folder doens't exist create
        if (!FileSystem::FileSystem::Exists(cachePath)) {
            FileSystem::FileSystem::CreateDirectory(cachePath);
        }

        // get all paths
        // tuple same names into vert & frag
        // send to importer with save path
        FileSystem::Directory directory { rawPath };
        auto files = directory.GetFiles(true);

        for (const auto& vertexPath : files) {
            if (vertexPath.GetExtension() == ".vert") {
                auto name = vertexPath.GetName();

                auto fragmentPath = vertexPath;
                fragmentPath.ReplaceExtension(".frag");

                auto exportPath = cachePath + name;
                exportPath.ReplaceExtension(".meowdata");

                ShaderImporter::Import(exportPath, vertexPath, fragmentPath);
            }
        }
    }
}
