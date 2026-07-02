//
// Created by Akira Mujawar on 18/04/26.
//

#ifndef MEOWENGINE_RENDERSCENEDATA_HPP
#define MEOWENGINE_RENDERSCENEDATA_HPP

#include <GridDrawData.hpp>
#include <SkyboxDrawData.hpp>
#include <MeshDrawData.hpp>

#include <BoxColliderDrawData.hpp>
#include <SphereColliderDrawData.hpp>
#include <LineDrawData.hpp>
#include <TransformGizmoDrawData.hpp>

namespace MeowEngine::Rendering {
    struct RenderSceneData {
        // runtime
        SkyboxDrawData Skybox;
        std::vector<MeshDrawData> Meshes;

        // editor
        GridDrawData Grid; // this goes to renderer pass config
        std::vector<BoxColliderDrawData> BoxColliders;
        std::vector<SphereColliderDrawData> SphereColliders;
        std::vector<LineDrawData> Lines;
        std::vector<TransformGizmoDrawData> TransformGizmos; // this will allow multi selection
    };
}

#endif //MEOWENGINE_RENDERSCENEDATA_HPP