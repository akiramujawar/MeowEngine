//
// Created by Akira Mujawar on 21/05/26.
//

#ifndef MEOWENGINE_RENDERMESHHANDLE_HPP
#define MEOWENGINE_RENDERMESHHANDLE_HPP

#include <IRenderHandle.hpp>

namespace MeowEngine::Rendering {
    struct MeshRenderHandle : IRenderHandle {
        MeshRenderHandle();
        ~MeshRenderHandle() override;

    private:
        Asset::AssetHandle MeshAsset;
    };
}

#endif //MEOWENGINE_RENDERMESHHANDLE_HPP