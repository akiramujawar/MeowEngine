//
// Created by Akira Mujawar on 18/05/26.
//

#ifndef MEOWENGINE_GIZMOPASSDATA_HPP
#define MEOWENGINE_GIZMOPASSDATA_HPP

#include <vector>

#include <LineDrawData.hpp>
#include <BoxColliderDrawData.hpp>
#include <SphereColliderDrawData.hpp>

namespace MeowEngine::Rendering {
    struct GizmoPassData {
        std::vector<LineDrawData> Lines;
        std::vector<BoxColliderDrawData> BoxColliders;
        std::vector<SphereColliderDrawData> SphereColliders;
    };
}

#endif //MEOWENGINE_GIZMOPASSDATA_HPP

// for each pipeline
// RenderCommand::DrawMesh
// RenderCommand::DrawLine

// Passes call the RenderCommand
// for e.g.
// GizmoPass(passdata data)
// -> call RenderCommand::DrawLine(data.lines)
// -> call RenderCommand::DrawBoxCollider(data.spheres)
// -> call RenderCommand::DrawSphereCollider(data.boxes)
// GeometryPass
// -> call RenderCommand::DrawMesh(data.meshes)

// pipeline is setup for rendering
// has setup for init & shader program
// different pipelines might have same setup or same shader.
// like OpaqueMeshPipeline, WireframeMeshPipeline, WireframeColliderPipeline
// here opqueMeshPipline & wireframemeshpipline use same shader but different setup
// & wireframe collider pipline & wireframemeshpipline use same setup but different shader
// eg..
// OpaqueMeshPipeline.Bind();
// MeshRenderer.Draw(meshData);
//
// WireframeMeshPipeline.Bind();
// MeshRenderer.Draw(meshData);
//
// ColliderWireframePipeline.Bind();
// BoxColliderRenderer.Draw(boxData);