//
// Created by Akira Mujawar on 21/06/24.
//

#ifndef MEOWENGINE_OPENGL_RENDER_SYSTEM_HPP
#define MEOWENGINE_OPENGL_RENDER_SYSTEM_HPP

#include "internal_ptr.hpp"

#include "opengl_asset_manager.hpp"
#include "ImguiEditorUISystem.hpp"
#include "perspective_camera.hpp"

#include <memory>

namespace MeowEngine {
    struct OpenGLRenderSystem  {
        OpenGLRenderSystem(const std::shared_ptr<MeowEngine::OpenGLAssetManager>& assetManager,
                           const std::shared_ptr<Runtime::ImGuiUISystem>& uiRenderer);

        void RenderGameView(MeowEngine::PerspectiveCamera* cameraObject, entt::registry& registry, MeowEngine::SelectionData& pSelection);
        void RenderUserInterface(entt::registry& registry,
                                 std::queue<std::shared_ptr<MeowEngine::ReflectionPropertyChange>>& inUIInputQueue,
                                 MeowEngine::SelectionData& pSelection,
                                 unsigned int frameBufferId,
                                 const double fps);

        void RenderPhysics(MeowEngine::PerspectiveCamera* cameraObject, entt::registry& registry);

    private:
        struct Internal;
        MeowEngine::internal_ptr<Internal> InternalPointer;
    };
}


#endif //MEOWENGINE_OPENGL_RENDER_SYSTEM_HPP
