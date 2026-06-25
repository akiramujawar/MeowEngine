//
// Created by Akira Mujawar on 14/05/26.
//

#include <GLRender.hpp>

#include <GL_API.hpp>
#include <GLSceneViewBuffer.hpp>

namespace MeowEngine::Rendering {

    GLRender::GLRender() {
        SceneViewFrameBuffer = std::make_shared<GLSceneViewBuffer>(1000, 1000);
    }

    GLRender::~GLRender() {}

    void GLRender::Clear() {
        glClearColor(38 / 255.0f, 38 / 255.0f, 38 / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    std::shared_ptr<ISceneFrameBuffer> GLRender::GetSceneFrameBuffer() {
        return SceneViewFrameBuffer;
    }
}
