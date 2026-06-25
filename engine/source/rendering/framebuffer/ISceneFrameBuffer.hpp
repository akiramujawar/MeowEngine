//
// Created by Akira Mujawar on 25/06/26.
//

#ifndef MEOWENGINE_ISCENEFRAMEBUFFER_HPP
#define MEOWENGINE_ISCENEFRAMEBUFFER_HPP

namespace MeowEngine::Rendering {

    class ISceneFrameBuffer {
    public:
        virtual ~ISceneFrameBuffer() = default;

        virtual unsigned int GetFrameTexture() = 0;
        virtual void RescaleFrameBuffer(const float& width, const float& height) = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };

}

#endif //MEOWENGINE_ISCENEFRAMEBUFFER_HPP