//
// Created by Akira Mujawar on 28/02/26.
//

#ifndef MEOWENGINE_IMGUIASSETDRAGDROP_HPP
#define MEOWENGINE_IMGUIASSETDRAGDROP_HPP

#include <string>
#include "DirectoryAsset.hpp"


namespace MeowEngine::Editor {
    class ImguiAssetDragDrop {
    public:
        // TODO: later change this to uuid
        // along with that we can use asset loader to show thumbnail. Hence forth we only pass Path
        /**
         *
         * @param path
         * @param name
         * @param imagePtr
         */
        static void DragAsset(const Asset::DirectoryAsset& asset, const std::string& name, void* imagePtr);
        static bool DropAssetOnAssetHandleInput(Asset::AssetHandle& asset);
        static bool DropAssetOnEntityHandleInput(Runtime::EntityHandle& handle);
        static void DropAssetOnFolder(const std::string& moveToPath);

        static void DragEntity(const Runtime::EntityHandle& entity);
        static bool DropEntity(Runtime::EntityHandle& entity);
    };
}


#endif //MEOWENGINE_IMGUIASSETDRAGDROP_HPP
