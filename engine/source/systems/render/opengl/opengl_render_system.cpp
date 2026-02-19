//
// Created by Akira Mujawar on 21/06/24.
//

#include "opengl_render_system.hpp"


#include "opengl_mesh_pipeline.hpp"
#include "opengl_line_pipeline.hpp"
#include "opengl_grid_pipeline.hpp"
#include "opengl_sky_box_pipeline.hpp"
#include "opengl_collider_pipeline.hpp"
#include "opengl_transform_handle_pipeline.hpp"

#include "transform_handle_component.hpp"
#include "grid_component.hpp"

using MeowEngine::OpenGLRenderSystem;

using namespace MeowEngine::pipeline;
using namespace MeowEngine::entity;
using namespace MeowEngine::component;

using MeowEngine::assets::ShaderPipelineType;

struct OpenGLRenderSystem::Internal {
    const std::shared_ptr<MeowEngine::OpenGLAssetManager> AssetManager;
    const std::shared_ptr<MeowEngine::graphics::ImGuiUserInterfaceSystem> UI;

    Internal(std::shared_ptr<MeowEngine::OpenGLAssetManager> assetManager,
             std::shared_ptr<MeowEngine::graphics::ImGuiUserInterfaceSystem> inUIRenderer)
    : AssetManager(assetManager)
    , UI(inUIRenderer){}

    void RenderGameView(MeowEngine::PerspectiveCamera* cameraObject, entt::registry& registry, MeowEngine::SelectionData& pSelection)
    {
//        auto view = registry.view<MeowEngine::core::component::Transform3DComponent>();
//        for(auto entity: view)
//        {
//            auto transform = view.get<MeowEngine::core::component::Transform3DComponent>(entity);
//
//        }

//        auto view = registry.view<entity::Transform3dComponent>();
//        registry.view<MeowEngine::entity::Transform3dComponent>().each([](auto entity, auto &MeowEngine::entity::Transform3dComponent) {
//            // ...
//        });
//
//        for(auto &&[entt::entity, MeowEngine::entity::Transform3dComponent]: registry.view<entity::Transform3dComponent>().each()) {
//            // ...
//        }

        // TODO: Find a cleaner way as manual query for render components for shader pipeline will result in editor code changes for every new shaders
        // TODO: This can be taken up once we start on improving our shader pipeline itself
        // Where-ever optimisation can be achieved remove it from such loop queries.
        // We know there's only one skybox or grid so no need to include that

        for(auto &&[entity,renderComponent, transform]: registry.view<entity::MeshRenderComponent, entity::Transform3DComponent>().each()) {
            AssetManager->GetShaderPipeline<OpenGLMeshPipeline>(ShaderPipelineType::Default)->Render(
                    *AssetManager,
                    &renderComponent,
                    &transform
            );
        }

        for(auto &&[entity,renderComponent]: registry.view<component::GridComponent>().each()) {
                AssetManager->GetShaderPipeline<OpenGLGridPipeline>(ShaderPipelineType::Grid)->Render(
                        *AssetManager,
                        &renderComponent,
                        cameraObject
                );
        }

        for(auto &&[entity,renderComponent]: registry.view<entity::SkyBoxComponent>().each()) {
                AssetManager->GetShaderPipeline<OpenGLSkyBoxPipeline>(ShaderPipelineType::Sky)->Render(
                        *AssetManager,
                        &renderComponent,
                        cameraObject
                );
        }

        if(registry.valid(pSelection.SelectedEntity)) {
            auto selectedTransform = registry.try_get<entity::Transform3DComponent>(pSelection.SelectedEntity);

            if(selectedTransform != nullptr) {
                for (auto &&[entity, renderComponent]: registry.view<entity::TransformHandleComponent>().each()) {
                    AssetManager->GetShaderPipeline<OpenGLTransformHandlePipeline>(
                            ShaderPipelineType::TRANSFORM_HANDLE)->Render(
                            *AssetManager,
                            &renderComponent,
                            selectedTransform,
                            cameraObject
                    );
                }
            }
        }
    }

    void RenderUserInterface(entt::registry& registry, std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue, MeowEngine::SelectionData& pSelection, unsigned int frameBufferId, const double fps) {
        UI.get()->Render(registry, inUIInputQueue, pSelection, frameBufferId, fps);
    }

    void RenderPhysics(MeowEngine::PerspectiveCamera* cameraObject, entt::registry& registry) {
        AssetManager->GetShaderPipeline<OpenGLColliderPipeline>(ShaderPipelineType::PHYSICS_COLLIDER)->Render(cameraObject, registry);
    }
};

OpenGLRenderSystem::OpenGLRenderSystem(const std::shared_ptr<MeowEngine::OpenGLAssetManager>& assetManager,
                                       const std::shared_ptr<MeowEngine::graphics::ImGuiUserInterfaceSystem>& uiRenderer)
    : InternalPointer(MeowEngine::make_internal_ptr<Internal>(assetManager, uiRenderer)) {}


void OpenGLRenderSystem::RenderGameView(MeowEngine::PerspectiveCamera* cameraObject, entt::registry& registry, MeowEngine::SelectionData& pSelection) {
    InternalPointer->RenderGameView(cameraObject, registry, pSelection);
}

void OpenGLRenderSystem::RenderUserInterface(entt::registry& registry, std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue, MeowEngine::SelectionData& pSelection, unsigned int frameBufferId, const double fps) {
    InternalPointer->RenderUserInterface(registry, inUIInputQueue, pSelection, frameBufferId, fps);
}

void OpenGLRenderSystem::RenderPhysics(MeowEngine::PerspectiveCamera* cameraObject, entt::registry& registry) {
    InternalPointer->RenderPhysics(cameraObject, registry);
}