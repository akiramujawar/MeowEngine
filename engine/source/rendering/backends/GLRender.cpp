//
// Created by Akira Mujawar on 14/05/26.
//

#include <GLRender.hpp>

#include <GL_API.hpp>

namespace MeowEngine::Rendering {

    GLRender::GLRender() {

    }

    GLRender::~GLRender() {}

    void GLRender::Clear() {
        glClearColor(38 / 255.0f, 38 / 255.0f, 38 / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
