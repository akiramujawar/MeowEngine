//
// Created by Akira Mujawar on 21/06/24.
//

#ifndef MEOWENGINE_ASSET_INVENTORY_HPP
#define MEOWENGINE_ASSET_INVENTORY_HPP

#pragma once

#include "assets.hpp"
#include <string>
#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::assets {
    enum class ShaderPipelineType {
        Default,
        Line,
        Grid,
        Sky,
        PHYSICS_COLLIDER,
        TRANSFORM_HANDLE
    };
    REFLECT_ENUM(MeowEngine::assets, ShaderPipelineType)

    enum class StaticMeshType {
        Plane,
        Cube,
        Sphere,
        Cylinder,
        Cone,
        Torus
    };
    REFLECT_ENUM(MeowEngine::assets, StaticMeshType)

    enum class TextureType {
        Default,
        Pattern
    };
    REFLECT_ENUM(MeowEngine::assets, TextureType)

    std::string ResolveShaderPipelinePath(const MeowEngine::assets::ShaderPipelineType& shaderPipeline);
    std::string ResolveStaticMeshPath(const MeowEngine::assets::StaticMeshType& staticMesh);
    std::string ResolveTexturePath(const MeowEngine::assets::TextureType& texture);
}


#endif //MEOWENGINE_ASSET_INVENTORY_HPP
