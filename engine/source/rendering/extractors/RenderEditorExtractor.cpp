//
// Created by Akira Mujawar on 12/06/26.
//

#include <RenderEditorExtractor.hpp>

#include <RenderSceneData.hpp>
#include <RenderUIData.hpp>

// runtime
#include <GameplaySystem.hpp>
#include <World.hpp>
#include "AssetManager.hpp"

// editor
#include <Selector.hpp>

// components
#include <IdentityComponent.hpp>
#include <InfoComponent.hpp>
#include <HierarchyComponent.hpp>
#include <Transform3DComponent.hpp>
#include <collider_component.hpp>

#include "CameraComponent.hpp"
#include "GridComponent.hpp"

namespace MeowEngine::Rendering {
    RenderEditorExtractor::RenderEditorExtractor() {}

    void RenderEditorExtractor::Init(const RenderExtractorInitData& context) {
        Gameplay = context.Gameplay;
        Selector = context.Selector;
        AssetManager = context.AssetManager;
    }

    void RenderEditorExtractor::ExtractScene(RenderSceneData& frame) {
        auto& world = Gameplay->GetWorld();
        auto& ecs = world.GetRegistry();
        const auto& camera = Gameplay->GetCamera();

        // selected transform handles
        for (auto &&handle : Selector->SelectedEntities) {
            auto transform = ecs.try_get<Runtime::Transform3DComponent>(handle.GetEntity());

            if (transform != nullptr) {
                Rendering::TransformHandleDrawData data {};
                data.Shader = ShaderRenderHandle(Asset::AssetHandle::Invalid);
                // data.TransformMatrix = transform->TransformMatrix;

                frame.TransformHandles.push_back(data);
            }
        }

        // grid
        auto grid = ecs.try_get<Runtime::GridComponent>(world.Grid.GetEntity());
        if (grid != nullptr) {
            if (AssetManager->HasAssetInDatabase(grid->GetShaderAssetHandle())) {
                AssetManager->GetAssetOrLoad<Asset::ShaderAsset>(grid->GetShaderAssetHandle());

                GridDrawData data;
                data.Shader = ShaderRenderHandle(grid->GetShaderAssetHandle());
                data.CameraViewMatrix = camera.GetView(); // camera
                data.CameraProjectionMatrix = camera.GetProjection(); // camera

                frame.Grid = data;
            }
            else {
                GridDrawData data;
                data.Shader = ShaderRenderHandle(Asset::AssetHandle::Invalid);

                frame.Grid = data;
            }
        }

        // physics colliders (box, sphere)
        auto&& collidersView = ecs.view<Runtime::Transform3DComponent, Runtime::ColliderComponent>();
        for (auto &&entity : collidersView) {
            auto&& [transform, collider] = collidersView.get(entity);

            switch (collider.GetColliderData().GetType()) {
                case Runtime::ColliderType::BOX: {
                    auto shape = collider.GetColliderData().Cast<Runtime::BoxColliderShape>();
                    BoxColliderDrawData data;
                    data.Shader = ShaderRenderHandle(Asset::AssetHandle::Invalid);
                    // data.TransformMatrix = transform.TransformMatrix; // process collider transform

                    frame.BoxColliders.push_back(data);
                    break;
                }

                case Runtime::ColliderType::SPHERE: {
                    auto shape = collider.GetColliderData().Cast<Runtime::SphereColliderShape>();
                    SphereColliderDrawData data;
                    data.Shader = ShaderRenderHandle(Asset::AssetHandle::Invalid);
                    // data.TransformMatrix = transform.TransformMatrix; // process collider transform

                    frame.SphereColliders.push_back(data);

                    break;
                }

                default:
                    break;
            }
        }

        // -- examples
        // auto view = registry.view<MeowEngine::core::component::Transform3DComponent>();
        // for(auto entity: view)
        // {
        //     auto transform = view.get<MeowEngine::core::component::Transform3DComponent>(entity);
        //
        // }
        //
        // auto view = registry.view<entity::Transform3dComponent>();
        // registry.view<MeowEngine::entity::Transform3dComponent>().each([](auto entity, auto &MeowEngine::entity::Transform3dComponent) {
        //     // ...
        // });
        //
        // for(auto &&[entt::entity, MeowEngine::entity::Transform3dComponent]: registry.view<entity::Transform3dComponent>().each()) {
        //     // ...
        // }
    }

    void RenderEditorExtractor::ExtractUI(RenderUIData& frame) {
        auto& world = Gameplay->GetWorld();
        auto& ecs = world.GetRegistry();

        // extract entities for tree panel
        auto view = ecs.view<Runtime::IdentityComponent, Runtime::InfoComponent, Runtime::HierarchyComponent>();
        std::function<void(Runtime::EntityHandle)> extractEntityHierarchy;

        // dynamic method for getting the child entities
        extractEntityHierarchy = [&ecs, &frame, &view, &extractEntityHierarchy](Runtime::EntityHandle handle) {
            auto&& [identity, info, hierarchy] = view.get(handle.GetEntity());

            std::vector<Runtime::EntityHandle> childs;
            Runtime::EntityHandle child = hierarchy.FirstChild;

            // recursively expand and get all child uuid's for given entity parent
            while (child.GetIsValid()) {
                extractEntityHierarchy(child);

                // track child uuid (for render data)
                auto childIdentity = ecs.get<Runtime::IdentityComponent>(child.GetEntity());
                childs.push_back(childIdentity.GetEntityHandle());

                // select to next child to iterate
                child = ecs.get<Runtime::HierarchyComponent>(child.GetEntity()).NextChildOfParent;
            }

            // track the entity data (for render data)
            frame.EntityHierarchyMap.emplace(identity.GetEntityHandle(), RenderEntityHierarchy {
                identity.GetEntityHandle(), info.GetName(), std::move(childs)
            });
        };

        // select only root entities and expand on them
        for (auto& entity : view) {
            auto&& hierarchy = ecs.get<Runtime::HierarchyComponent>(entity);

            // auto parent = hierarchy.Parent.GetEntity();

            // only select root entities (we expand childs inside)
            if (!hierarchy.Parent.GetIsValid()) {
                // track entity guid (only root)
                auto&& identity = ecs.get<Runtime::IdentityComponent>(entity);
                frame.RootEntities.push_back(identity.GetEntityHandle());

                // dive deep into childs
                extractEntityHierarchy(identity.GetEntityHandle());
            }
        }

        // track selected entities
        for (const auto handle : Selector->SelectedEntities) {
            // auto identity = ecs.get<Runtime::IdentityComponent>(handle.GetEntity());
            frame.SelectedEntities.emplace(handle);
        }

        // world inspector (copy selected entity)
        if (!Selector->SelectedEntities.empty()) {
            auto lastSelectedEntity = Selector->SelectedEntities[Selector->SelectedEntities.size() - 1];

            // track last selected entity guid
            auto identity = ecs.get<Runtime::IdentityComponent>(lastSelectedEntity.GetEntity());
            frame.LastSelectedEntity = lastSelectedEntity;

            // track component data for last selected entity
            if (ecs.valid(lastSelectedEntity.GetEntity())) {
                // for entity if a component exists capture it's type, name & data & create a relfected clone
                for (pair<unsigned int, entt::basic_sparse_set<Runtime::Entity>&> component: ecs.storage()) {
                    // find the component type, name and object data from ecs registry
                    if (component.second.contains(lastSelectedEntity.GetEntity())) {
                        const Runtime::EntityComponent componentType = component.first;
                        const std::string componentName = MeowEngine::GetReflection().GetComponentName(componentType);
                        void* componentObject = component.second.value(lastSelectedEntity.GetEntity());

                        void* clonedComponent = GetReflection().CopyComponentData(componentType, componentName, componentObject);

                        frame.LastSelectedEntityComponents.push_back({
                            componentType,
                            componentName,
                            clonedComponent
                        });
                    }
                }
            }
        }

        // cache the selected file / folder
        frame.SelectedFolderPath = Path(Selector->SelectedDirectoryPath);
        frame.SelectedFilePath = Path(Selector->SelectedAssetPath);

        // for now, we shallow copy
        // TODO: implement this properly before multithreading to avoid race coniditons
        frame.EngineDirectoryMap = AssetManager->GetDirectory().EngineFolderCache;
        frame.SandboxDirectoryMap = AssetManager->GetDirectory().SandboxFolderCache;

        frame.FilesInSelectedFolder = AssetManager->GetDirectory().GetAssets(frame.SelectedFolderPath);
    }

    void RenderEditorExtractor::Clear(RenderSceneData& sceneData, RenderUIData& uiData) {
        // TODO: for now we clear every frame, but later make on trigger basis
        // we dont need to copy data which has low update frequency.

        // clear scene data
        sceneData.BoxColliders.clear();
        sceneData.SphereColliders.clear();
        sceneData.Lines.clear();
        sceneData.TransformHandles.clear();

        // clear ui data
        uiData.RootEntities.clear();
        uiData.EntityHierarchyMap.clear();
        uiData.SelectedEntities.clear();
        // -- delete & clear copied components
        for (auto& lastSelectedComponent : uiData.LastSelectedEntityComponents) {
            GetReflection().DeleteComponentData(lastSelectedComponent.Type, lastSelectedComponent.DataObject);
        }
        uiData.LastSelectedEntityComponents.clear();
    }
}
