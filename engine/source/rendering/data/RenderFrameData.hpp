//
// Created by Akira Mujawar on 18/04/26.
//

#ifndef MEOWENGINE_RENDERFRAMEDATA_HPP
#define MEOWENGINE_RENDERFRAMEDATA_HPP

#include <GridDrawData.hpp>
#include <SkyBoxDrawData.hpp>
#include <MeshDrawData.hpp>

#include <BoxColliderDrawData.hpp>
#include <SphereColliderDrawData.hpp>
#include <LineDrawData.hpp>
#include <TransformHandleDrawData.hpp>


namespace MeowEngine::Rendering {
    struct RenderFrameData {
        GridDrawData Grid; // this goes to renderer pass config
        SkyBoxDrawData SkyBox;
        std::vector<MeshDrawData> Meshes;
        std::vector<BoxColliderDrawData> BoxColliders;
        std::vector<SphereColliderDrawData> SphereColliders;
        std::vector<LineDrawData> Lines;
        std::vector<TransformHandleDrawData> TransformHandles; // this will allow multi selection
    };
}

#endif //MEOWENGINE_RENDERFRAMEDATA_HPP