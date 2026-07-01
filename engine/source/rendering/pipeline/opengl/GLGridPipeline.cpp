//
// Created by Akira Mujawar on 22/06/24.
//

#include "GLGridPipeline.hpp"

#include <log.hpp>
#include <GL_API.hpp>
#include <RenderContext.hpp>
#include <RenderResourceManager.hpp>
#include <GLShaderResource.hpp>
#include "GridDrawData.hpp"

namespace MeowEngine::Rendering {
    OpenGLGridPipeline::OpenGLGridPipeline() {
        glGenVertexArrays(1, &VertexArrayID);
    }

    OpenGLGridPipeline::~OpenGLGridPipeline() {
        glDeleteVertexArrays(1, &VertexArrayID);
    }

    void OpenGLGridPipeline::Draw(const RenderContext& context, GridDrawData& data) const {
        if (!data.Shader.IsValid()) {
            return;
        }

        const auto& shader = context.ResourceManager->GetShaderResource(data.Shader);

        glUseProgram(shader.GetID());

        // NOTE: how can we optimise this further?
        glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "u_view"), 1, GL_FALSE, &data.CameraViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "u_projection"), 1, GL_FALSE, &data.CameraProjectionMatrix[0][0]);

        glBindVertexArray(VertexArrayID);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

}
