//
// Created by Akira Mujawar on 14/05/26.
//

#include <GLRenderAPI.hpp>

#include <OpenGLAPI.hpp>

namespace MeowEngine::Rendering {

    GLRenderAPI::GLRenderAPI() {}

    GLRenderAPI::~GLRenderAPI() {}

    void GLRenderAPI::Clear() {
        glClearColor(38 / 255.0f, 38 / 255.0f, 38 / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

}
