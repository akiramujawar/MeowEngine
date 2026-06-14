//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_IMGUIRENDER_HPP
#define MEOWENGINE_IMGUIRENDER_HPP

#include <IUIRender.hpp>

namespace MeowEngine::Rendering {
    class ImGuiRender : public IUIRender {
    public:
        ImGuiRender(Graphics::GraphicsDevice& device);
        ~ImGuiRender() override;

        void Init(RendererInitData& context) override;
        void SaveLayout() override;

        /**
         * Start recording Render Commands for ScreenSpace UI
         */
        void BeginFrame() override;

        /**
         * End recording Render Commands for ScreenSpace UI
         */
        void EndFrame() override;

        /**
         * Execute the Render Commands to draw ScreenSpace UI
         */
        void DrawFrame() override;

        void ProcessInputEvent(const SDL_Event& event) override;
    };
}


#endif //MEOWENGINE_IMGUIRENDER_HPP