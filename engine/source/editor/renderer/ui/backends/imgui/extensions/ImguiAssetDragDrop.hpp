//
// Created by Akira Mujawar on 28/02/26.
//

#ifndef MEOWENGINE_IMGUIASSETDRAGDROP_HPP
#define MEOWENGINE_IMGUIASSETDRAGDROP_HPP

#include "string"

namespace MeowEngine::Editor::UI {
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
        static void DragAsset(const std::string& path, const std::string& name, void* imagePtr);
        static void DropAsset(const std::string& moveToPath);
    };
}


#endif //MEOWENGINE_IMGUIASSETDRAGDROP_HPP
