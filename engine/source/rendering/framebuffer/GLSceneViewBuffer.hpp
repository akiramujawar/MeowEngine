//
// Created by Akira Mujawar on 10/07/24.
//

#ifndef MEOWENGINE_GLSCENEVIEWBUFFER_HPP
#define MEOWENGINE_GLSCENEVIEWBUFFER_HPP

#include "ISceneFrameBuffer.hpp"

namespace MeowEngine::Rendering {
    /**
     * Renders world on a viewport (ui panel / texture)
     * TODO: this needs to be migrated/rewritten at the time of using RenderCommand
     */
    struct GLSceneViewBuffer : ISceneFrameBuffer {
        GLSceneViewBuffer(const float& width, const float& height);
        ~GLSceneViewBuffer() override;

        unsigned int GetFrameTexture() override;
        void RescaleFrameBuffer(const float& width, const float& height) override;

        void Bind() const override;
        void Unbind() const override;

    private:
        unsigned int frameBufferId;
        unsigned int textureId;
        unsigned int renderBufferId;
    };
}


#endif //MEOWENGINE_GLSCENEVIEWBUFFER_HPP
