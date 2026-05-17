//
// Created by Akira Mujawar on 10/07/24.
//

#ifndef MEOWENGINE_GLWORLDVIEWBUFFER_HPP
#define MEOWENGINE_GLWORLDVIEWBUFFER_HPP

namespace MeowEngine::Graphics {
    /**
     * Renders world on a viewport (ui panel / texture)
     * TODO: this needs to be migrated/rewritten at the time of using RenderCommand
     */
    struct GLWorldViewBuffer {
        GLWorldViewBuffer(const float& width, const float& height);
        ~GLWorldViewBuffer();

        unsigned  int GetFrameTexture();
        void RescaleFrameBuffer(const float& width, const float& height);
        void Bind() const;
        void Unbind() const;

    private:
        unsigned int frameBufferId;
        unsigned int textureId;
        unsigned int renderBufferId;
    };
}


#endif //MEOWENGINE_GLWORLDVIEWBUFFER_HPP
