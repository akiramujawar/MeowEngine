//
// Created by Akira Mujawar on 10/07/24.
//

#ifndef MEOWENGINE_OPENGL_FRAMEBUFFER_HPP
#define MEOWENGINE_OPENGL_FRAMEBUFFER_HPP

namespace MeowEngine::Graphics {
    struct GLWorldViewFrameBuffer {
        GLWorldViewFrameBuffer(const float& width, const float& height);
        ~GLWorldViewFrameBuffer();

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


#endif //MEOWENGINE_OPENGL_FRAMEBUFFER_HPP
