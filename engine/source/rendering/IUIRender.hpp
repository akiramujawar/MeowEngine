//
// Created by Akira Mujawar on 17/05/26.
//

#ifndef MEOWENGINE_IUIRENDER_HPP
#define MEOWENGINE_IUIRENDER_HPP

namespace MeowEngine::Graphics {
    class GraphicsDevice;
}

namespace MeowEngine::Rendering {
    class IUIRender {
    public:
        virtual ~IUIRender() = default;

        /**
         * Start recording Render Commands for ScreenSpace UI
         */
        virtual void BeginFrame() = 0;

        /**
         * End recording Render Commands for ScreenSpace UI
         */
        virtual void EndFrame() = 0;

        /**
         * Execute the Render Commands to draw ScreenSpace UI
         */
        virtual void DrawFrame() = 0;
    };
}

#endif //MEOWENGINE_IUIRENDER_HPP