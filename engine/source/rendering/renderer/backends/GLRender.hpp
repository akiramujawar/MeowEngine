//
// Created by Akira Mujawar on 14/05/26.
//

#ifndef MEOWENGINE_GLRENDERAPI_HPP
#define MEOWENGINE_GLRENDERAPI_HPP

#include <IRenderAPI.hpp>

namespace MeowEngine::Rendering {
    class GLRender : public IRenderAPI {
    public:
        explicit GLRender();
        ~GLRender() override;

        void Clear() override;
        void SetViewportSize(int width, int height) override;

        std::shared_ptr<ISceneFrameBuffer> GetSceneFrameBuffer() override;

    private:
        /**
         * Draws our game view onto a ui panel (which is a framebuffer)
         */
        std::shared_ptr<ISceneFrameBuffer> SceneViewFrameBuffer;
    };
}


#endif //MEOWENGINE_GLRENDERAPI_HPP