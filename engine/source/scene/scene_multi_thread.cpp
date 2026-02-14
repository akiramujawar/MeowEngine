//
// Created by Akira Mujawar on 21/06/24.
//

#include "scene_multi_thread.hpp"

#include "camera_controller.hpp"
#include "perspective_camera.hpp"
#include "static_mesh_instance.hpp"
#include "log.hpp"
#include "opengl_line_pipeline.hpp"

#include "camera_component.hpp"
#include "mesh_render_component.hpp"
#include "line_render_component.hpp"
#include "transform2d_component.hpp"
#include "transform3d_component.hpp"

#include "life_object_component.hpp"
#include "transform3d_component.hpp"
#include "box_collider_data.hpp"
#include "collider_component.hpp"
#include "reflection_test_component.hpp"

#include "sky_box_component.hpp"

#include "rigidbody_component.hpp"
#include "entt_triple_buffer.hpp"
#include "reflection_macro_wrapper.hpp"

#include "physx_physics_system.hpp"

using MeowEngine::SceneMultiThread;


using namespace MeowEngine::assets;
using namespace MeowEngine::entity;

namespace {
    MeowEngine::PerspectiveCamera CreateCamera(const MeowEngine::WindowSize& size) {
        return MeowEngine::PerspectiveCamera(static_cast<float>(size.Width), static_cast<float>(size.Height));
    }
}

// this -> type -> value
// component -> property -> property

struct SceneMultiThread::Internal {
    MeowEngine::PerspectiveCamera Camera;
    MeowEngine::CameraController CameraController;

    EnttTripleBuffer RegistryBuffer;

    // User Input Events
    const uint8_t* KeyboardState; // SDL owns the object & will manage the lifecycle. We just keep a pointer.

    Internal(const MeowEngine::WindowSize& size)
        : Camera(::CreateCamera(size))
        , CameraController({glm::vec3(0.0f, 2.0f , -10.0f)})
        , KeyboardState(SDL_GetKeyboardState(nullptr))
        , RegistryBuffer()
    {
        MeowEngine::Log("MainScene", "Scene Created");
    }

    void OnWindowResized(const MeowEngine::WindowSize& size) {
        Camera = ::CreateCamera(size);
    }

    void LoadOnRenderThread(std::shared_ptr<MeowEngine::AssetManager> assetManager) {
        assetManager->LoadShaderPipelines({
                                                  assets::ShaderPipelineType::Grid,
                                                  assets::ShaderPipelineType::Default,
                                                  assets::ShaderPipelineType::Line,
                                                  assets::ShaderPipelineType::Sky,
                                                  assets::ShaderPipelineType::PHYSICS_COLLIDER
                                          });

        assetManager->LoadStaticMeshes({
                                               assets::StaticMeshType::Plane,
                                               assets::StaticMeshType::Cube,
                                               assets::StaticMeshType::Sphere,
                                               assets::StaticMeshType::Cylinder,
                                               assets::StaticMeshType::Cone,
                                               assets::StaticMeshType::Torus
                                       });

        assetManager->LoadTextures({
                                           assets::TextureType::Default,
                                           assets::TextureType::Pattern
                                   });

        // register components in entt buffer.
        // this helps to dynamically manage add/remove components at runtime
        // considering & respects all threads.
#ifdef __MULTI_THREAD__
        MeowEngine::GetReflection().InitialiseComponents(RegistryBuffer);
#endif
    }

    bool AddEntitiesOnPhysicsThread(MeowEngine::simulator::PhysicsSystem* inPhysics) {
        return RegistryBuffer.ApplyAddRemoveOnStaging(inPhysics);
    }

    void CreateSceneOnMainThread() {
        auto entity = RegistryBuffer.AddEntity();
        RegistryBuffer.AddComponent<entity::LifeObjectComponent>(entity, "Torus");
        RegistryBuffer.AddComponent<entity::Transform3DComponent>(
                entity,
                Camera.GetProjectionMatrix() * Camera.GetViewMatrix(),
                math::Vector3{5, 5, 5},
                math::Vector3{1.0, 1.0f, 1.0f},
                glm::vec3{0.0f, 1.0f, 0.0f},
                12.0f
        );
        RegistryBuffer.AddComponent<entity::MeshRenderComponent>(
                entity,
                assets::ShaderPipelineType::Default,
                new MeowEngine::StaticMeshInstance{
                        assets::StaticMeshType::Torus,
                        assets::TextureType::Pattern
                }
        );
        RegistryBuffer.AddComponent<entity::ReflectionTestComponent>(
            entity
        );

        for(int i = 0 ; i < 1; i++){
            const auto cubeTest = RegistryBuffer.AddEntity();
            RegistryBuffer.AddComponent<entity::LifeObjectComponent>(cubeTest, "Cube (" + std::to_string(i) + ")");
            RegistryBuffer.AddComponent<entity::Transform3DComponent>(
                    cubeTest,
                    Camera.GetProjectionMatrix() * Camera.GetViewMatrix(),
                    math::Vector3{0.0f, 5.0f + i, 2},
                    math::Vector3{0.5f, 0.5f,0.5f},
                    glm::vec3{0.0f, 1.0f, 0.0f},
                    0
            );
            RegistryBuffer.AddComponent<entity::MeshRenderComponent>(
                    cubeTest,
                    assets::ShaderPipelineType::Default,
                    new MeowEngine::StaticMeshInstance{
                            assets::StaticMeshType::Cube,
                            assets::TextureType::Pattern
                    }
            );
            MeowEngine::entity::BoxColliderData colliderData {MeowEngine::math::Vector3(1,1,1)};
            RegistryBuffer.AddComponent<entity::ColliderComponent>(
                    cubeTest,
                    colliderData
            );
            RegistryBuffer.AddComponent<entity::RigidbodyComponent>(
                    cubeTest
            );
        }

        for(int i = 0 ; i < 0; i++){
            const auto sphereTest = RegistryBuffer.AddEntity();
            RegistryBuffer.AddComponent<entity::LifeObjectComponent>(sphereTest, "Sphere (" + std::to_string(i) + ")");
            RegistryBuffer.AddComponent<entity::Transform3DComponent>(
                    sphereTest,
                    Camera.GetProjectionMatrix() * Camera.GetViewMatrix(),
                    math::Vector3{0.0f, 20.0f + i, 2},
                    math::Vector3{0.5f, 0.5f,0.5f},
                    glm::vec3{0.0f, 1.0f, 0.0f},
                    0
            );
            RegistryBuffer.AddComponent<entity::MeshRenderComponent>(
                    sphereTest,
                    assets::ShaderPipelineType::Default,
                    new MeowEngine::StaticMeshInstance{
                            assets::StaticMeshType::Sphere,
                            assets::TextureType::Pattern
                    }
            );

            MeowEngine::entity::SphereColliderData colliderData {0.5f};
            RegistryBuffer.AddComponent<entity::ColliderComponent>(
                    sphereTest,
                    colliderData
            );
            RegistryBuffer.AddComponent<entity::RigidbodyComponent>(
                    sphereTest
            );
        }

//
//
//        // setup object
//        // later query for all rigidbody, get the physx, get the collider and construct for physics
//
//        const auto cameraEntity = RegistryBuffer.AddEntity();
//        RegistryBuffer.AddComponent<entity::LifeObjectComponent>(cameraEntity, "Camera");
//        RegistryBuffer.AddComponent<entity::Transform3DComponent>(
//            cameraEntity,
//            Camera.GetProjectionMatrix() * Camera.GetViewMatrix(),
//            math::Vector3{0, 0, 0},
//            math::Vector3{1.0, 1.0f, 1.0f},
//            glm::vec3{0.0f, 1.0f, 0.0f},
//            0.0f
//        );
//        RegistryBuffer.AddComponent<entity::CameraComponent>(
//            cameraEntity
//        );
//
//
        const auto gridEntity = RegistryBuffer.AddEntity();
        RegistryBuffer.AddComponent<entity::LifeObjectComponent>(gridEntity, "Grid");
        RegistryBuffer.AddComponent<entity::Transform3DComponent>(
                gridEntity,
                Camera.GetProjectionMatrix() * Camera.GetViewMatrix(),
                math::Vector3{0, 0, 0},
                math::Vector3{1.0, 1.0f, 1.0f},
                glm::vec3{0.0f, 1.0f, 0.0f},
                0.0f
        );
        RegistryBuffer.AddComponent<entity::RenderComponentBase>(
            gridEntity,
            assets::ShaderPipelineType::Grid
        );

        const auto skyEntity = RegistryBuffer.AddEntity();
        RegistryBuffer.AddComponent<entity::LifeObjectComponent>(skyEntity, "Sky Box");
        RegistryBuffer.AddComponent<entity::Transform3DComponent>(
                skyEntity,
                Camera.GetProjectionMatrix() * Camera.GetViewMatrix(),
                math::Vector3{0, 0, 0},
                math::Vector3{1.0, 1.0f, 1.0f},
                glm::vec3{0.0f, 1.0f, 0.0f},
                0.0f
        );
        RegistryBuffer.AddComponent<entity::SkyBoxComponent>(
                skyEntity,
                assets::ShaderPipelineType::Sky
        );

        MeowEngine::Log("Scene Multi-thread", "Created on main thread");
    }

    bool AddRemoveEntitiesOnMainThread() {
        return RegistryBuffer.ApplyAddRemoveOnCurrentFinal();
    }

    void Input(const float& delta, const MeowEngine::input::InputManager& inputManager) {
        if(!inputManager.isActive) {
            return;
        }

        if(inputManager.mouseState & SDL_BUTTON_LMASK) {
            CameraController.LookAround(inputManager.mouseDeltaX, inputManager.mouseDeltaY);
        }

        if(inputManager.isMouseDown && (inputManager.mouseState & SDL_BUTTON_RMASK)) {
            const auto cubeEntity = RegistryBuffer.AddEntity();
            RegistryBuffer.AddComponent<entity::LifeObjectComponent>(cubeEntity, "Cube");
            RegistryBuffer.AddComponent<entity::Transform3DComponent>(
                    cubeEntity,
                    Camera.GetProjectionMatrix() * Camera.GetViewMatrix(),
                    math::Vector3{0.0f, 20.0f, 2},
                    math::Vector3{0.5f, 0.5f,0.5f},
                    glm::vec3{0.0f, 1.0f, 0.0f},
                    0
            );
            RegistryBuffer.AddComponent<entity::MeshRenderComponent>(
                    cubeEntity,
                    assets::ShaderPipelineType::Default,
                    new MeowEngine::StaticMeshInstance{
                            assets::StaticMeshType::Cube,
                            assets::TextureType::Pattern
                    }
            );
            RegistryBuffer.AddComponent<entity::ColliderComponent>(
                    cubeEntity,
                    entity::BoxColliderData {}
            );
            RegistryBuffer.AddComponent<entity::RigidbodyComponent>(
                    cubeEntity
            );
        }

        if (KeyboardState[SDL_SCANCODE_UP] || KeyboardState[SDL_SCANCODE_W]) {
            CameraController.MoveForward(delta);
        }

        if (KeyboardState[SDL_SCANCODE_DOWN] || KeyboardState[SDL_SCANCODE_S]) {
            CameraController.MoveBackward(delta);
        }

        if (KeyboardState[SDL_SCANCODE_Q] ) {
            CameraController.MoveUp(delta);
        }

        if (KeyboardState[SDL_SCANCODE_E]) {
            CameraController.MoveDown(delta);
        }

//        if (KeyboardState[SDL_SCANCODE_LEFT] || KeyboardState[SDL_SCANCODE_A]) {
//            CameraController.TurnLeft(delta);
//        }
//
//        if (KeyboardState[SDL_SCANCODE_RIGHT] || KeyboardState[SDL_SCANCODE_D]) {
//            CameraController.TurnRight(delta);
//        }
    }

    // We can perform -> culling, input detection
    void Update(const float& deltaTime) {
        Camera.Configure(CameraController.GetPosition(), CameraController.GetUp(), CameraController.GetDirection());

        const glm::mat4 cameraMatrix {Camera.GetProjectionMatrix() * Camera.GetViewMatrix()};

//        for(auto& lifeObject : LifeObjects) {
//            lifeObject.TransformComponent->Update(cameraMatrix);
//        }

//        MeowEngine::Log("Camera", std::to_string(Camera.GetPosition().z));

        auto view = RegistryBuffer.GetCurrent().view<entity::Transform3DComponent>();
        for(auto entity: view) {
            auto& transform = view.get<entity::Transform3DComponent>(entity);
            transform.Update(deltaTime);
            transform.CalculateTransformMatrix(cameraMatrix);
        }

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
//        for(auto &&[entity,renderComponent, transform]: registry.view<entity::MeshRenderComponent, entity::Transform3DComponent>().each())
//        {
//            AssetManager->GetShaderPipeline<OpenGLMeshPipeline>(ShaderPipelineType::Default)->Render(
//                    *AssetManager,
//                    &renderComponent,
//                    &transform
//            );
//        }
//
//        for(auto &&[entity,renderComponent, transform]: registry.view<entity::RenderComponentBase, entity::Transform3DComponent>().each())
//        {
//            AssetManager->GetShaderPipeline<OpenGLGridPipeline>(ShaderPipelineType::Grid)->Render(
//                    *AssetManager,
//                    &renderComponent,
//                    &transform,
//                    cameraObject
//            );
//        }
    }

    void RenderGameView(MeowEngine::RenderSystem& renderer) {
        // This is important for now - we can come to this later for optimization
        // Current goal is to have full control on render as individual objects
        // as we will have elements like UI, Static Meshes, Post Processing, Camera Culling, Editor Tools
//        for(auto& lifeObject : LifeObjects) {
//            renderer.Render(&Camera, &lifeObject);
//        }
        renderer.RenderGameView(&Camera, RegistryBuffer.GetFinal());
        renderer.RenderPhysics(&Camera, RegistryBuffer.GetFinal());
    }

    void RenderUserInterface(MeowEngine::RenderSystem& renderer, unsigned int frameBufferId, const double fps) {
        renderer.RenderUserInterface(RegistryBuffer.GetFinal(), RegistryBuffer.GetPropertyChangeQueue() , frameBufferId, fps);
    }

    void SwapMainAndRenderBufferOnMainThread() {
        RegistryBuffer.SwapBuffer();
    }

    void SyncPhysicsBufferOnMainThread(bool inIsPhysicsThreadWorking) {
        auto currentView = RegistryBuffer.GetCurrent().view<MeowEngine::entity::Transform3DComponent, MeowEngine::entity::RigidbodyComponent>();
        auto stagingView = RegistryBuffer.GetStaging().view<MeowEngine::entity::Transform3DComponent, MeowEngine::entity::RigidbodyComponent>();
        auto finalView = RegistryBuffer.GetFinal().view<MeowEngine::entity::Transform3DComponent, MeowEngine::entity::RigidbodyComponent>();

        // the bool is atomic and results in locking mechanism to make sure sync is done
        // in order to prevent bad memory data reads
        if(inIsPhysicsThreadWorking) {
            // since physics is working on its buffer (staging) we cache the main thread updates
            // is this even necessary?
            for(entt::entity entity : currentView) {

                auto& staging = stagingView.get<MeowEngine::entity::RigidbodyComponent>(entity);
                auto final = finalView.get<MeowEngine::entity::Transform3DComponent>(entity);
                auto current = currentView.get<MeowEngine::entity::Transform3DComponent>(entity);

                // TODO: check on this once, this could lead multiple cache copies
                staging.CacheDelta(current.Position - final.Position, math::Quaternion::Multiply(
                    current.Quaternion,
                    math::Quaternion::Inverse(final.Quaternion)
                ));
            }
        }
        else {
            // since physics is not working, we can update rigidbody in physics thread
            // remember: physics & main applies transformations on its own.
            // in that case, we let physics take the ownership of data & get delta changes from main thread
            for (entt::entity entity: currentView) {
                auto &final = finalView.get<MeowEngine::entity::Transform3DComponent>(entity);
                auto &current = currentView.get<MeowEngine::entity::Transform3DComponent>(entity);

                auto staging = stagingView.get<MeowEngine::entity::Transform3DComponent>(entity);
                auto &rigidbody = stagingView.get<MeowEngine::entity::RigidbodyComponent>(entity);

                // Update physics body with transformation updates from main / final buffers
                rigidbody.AddDelta(current.Position - final.Position, math::Quaternion::Multiply(
                        current.Quaternion,
                        math::Quaternion::Inverse(final.Quaternion)
                ));

                // Update main buffer with rigidbody transformations
                current.Position = staging.Position;
//                current.Scale = staging.Scale;
                current.Rotation = staging.Rotation;
                current.Quaternion = staging.Quaternion;
            }
        }
    }

    void SyncRenderBufferOnMainThread() {
        // Add a template method to apply changes
        // Each component will have a apply data method
        // We will have data and component methods
        // Data will always my permanant with no apply data method
        // Components will always have apply method
        // Sync Transform Component
        auto currentView = RegistryBuffer.GetCurrent().view<MeowEngine::entity::Transform3DComponent>();
        auto finalView = RegistryBuffer.GetFinal().view<MeowEngine::entity::Transform3DComponent>();

        for(entt::entity entity : currentView) {
            auto current = currentView.get<MeowEngine::entity::Transform3DComponent>(entity);
            auto& final = finalView.get<MeowEngine::entity::Transform3DComponent>(entity);

            // any changes made on main thread, apply them on render thread (after this method they are swapped)
            // TODO: currently we do it manually, we need a better way to do this,
            // TODO: as manually apply changes could get difficult especially in long run
            final.Position = current.Position;
//            final.Scale = current.Scale;
            final.Rotation = current.Rotation;
            final.Quaternion = current.Quaternion;
        }

        // Apply UI inputs to render and main buffers
        // Push UI inputs for physics buffer (which gets processed in physics thread)
        RegistryBuffer.ApplyPropertyChange();
    }

    void SyncPhysicsBufferOnPhysicsThread(MeowEngine::simulator::PhysicsSystem* inPhysics) {
        // Apply update physics transform to entities
        auto view = RegistryBuffer.GetStaging().view<entity::Transform3DComponent, entity::RigidbodyComponent>();
        for(auto entity: view)
        {
            auto& transform = view.get<entity::Transform3DComponent>(entity);
            auto& rigidbody = view.get<entity::RigidbodyComponent>(entity);

            rigidbody.UpdateTransform(transform);
        }

        // Apply UI inputs to physics components
        RegistryBuffer.ApplyPropertyChangeOnStaging(inPhysics);
    }
};

SceneMultiThread::SceneMultiThread(const MeowEngine::WindowSize& size)
    : InternalPointer(MeowEngine::make_internal_ptr<Internal>(size)){}

void SceneMultiThread::OnWindowResized(const MeowEngine::WindowSize &size) {
    InternalPointer->OnWindowResized(size);
}

void SceneMultiThread::LoadOnRenderSystem(std::shared_ptr<MeowEngine::AssetManager> assetManager) {
    InternalPointer->LoadOnRenderThread(assetManager);
}
void SceneMultiThread::CreateSceneOnMainSystem() {
    InternalPointer->CreateSceneOnMainThread();
}

bool SceneMultiThread::AddRemoveEntitiesOnMainThread() {
    return InternalPointer->AddRemoveEntitiesOnMainThread();
}

bool SceneMultiThread::AddEntitiesOnPhysicsSystem(MeowEngine::simulator::PhysicsSystem* inPhysics) {
    return InternalPointer->AddEntitiesOnPhysicsThread(inPhysics);
}

void SceneMultiThread::Input(const float &deltaTime, const MeowEngine::input::InputManager& inputManager) {
    InternalPointer->Input(deltaTime, inputManager);
}

void SceneMultiThread::Update(const float &deltaTime) {
    InternalPointer->Update(deltaTime);
}

void SceneMultiThread::RenderGameView(MeowEngine::RenderSystem &renderer) {
    InternalPointer->RenderGameView(renderer);
}

void SceneMultiThread::RenderUserInterface(MeowEngine::RenderSystem &renderer, unsigned int frameBufferId, const double fps) {
    InternalPointer->RenderUserInterface(renderer, frameBufferId, fps);
}

void SceneMultiThread::SwapMainAndRenderBufferOnMainSystem() {
    InternalPointer->SwapMainAndRenderBufferOnMainThread();
}

void SceneMultiThread::SyncPhysicsBufferOnMainSystem(bool inIsPhysicsThreadWorking) {
    InternalPointer->SyncPhysicsBufferOnMainThread(inIsPhysicsThreadWorking);
}

void SceneMultiThread::SyncRenderBufferOnMainThread() {
    InternalPointer->SyncRenderBufferOnMainThread();
}

void SceneMultiThread::SyncPhysicsBufferOnPhysicsSystem(MeowEngine::simulator::PhysicsSystem* inPhysics) {
    InternalPointer->SyncPhysicsBufferOnPhysicsThread(inPhysics);
}











