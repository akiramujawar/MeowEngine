//
// Created by Akira Mujawar on 22/06/24.
//

#include <GLSkyboxPipeline.hpp>

#include <log.hpp>
#include <GL_API.hpp>
#include <RenderContext.hpp>
#include <RenderResourceManager.hpp>
#include <SkyboxDrawData.hpp>
#include <GLShaderResource.hpp>

namespace MeowEngine::Rendering {
    GLSkyboxPipeline::GLSkyboxPipeline() {
        MeowEngine::Log("GLSkyboxPipeline", "Constructed");

        glGenVertexArrays(1, &VertexArrayID);
    }

    GLSkyboxPipeline::~GLSkyboxPipeline() {
        MeowEngine::Log("GLSkyboxPipeline", "Constructed");

        glDeleteVertexArrays(1, &VertexArrayID);
    }

    void GLSkyboxPipeline::Draw(RenderContext& context, SkyboxDrawData& data) const {
        if (!data.Shader.IsValid()) {
            return;
        }

        const auto shader = context.ResourceManager->GetShaderResource(data.Shader);

        glUseProgram(shader.GetID());

        // NOTE: how can we optimise this further?
        glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "u_view"), 1, GL_FALSE, &data.CameraViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "u_projection"), 1, GL_FALSE, &data.CameraProjectionMatrix[0][0]);

        glBindVertexArray(VertexArrayID);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    // void GLSkyboxPipeline::Render(
    //         const MeowEngine::OpenGLAssetManager &assetManager,
    //         const MeowEngine::entity::SkyBoxComponent *renderComponent,
    //         const MeowEngine::PerspectiveCamera* camera) const {
    //
    //     glUseProgram(ShaderProgramID);\
    //
    //     //    auto now = high_resolution_clock::now();
    //     //    duration<float> elapsedTime = now - StartTime;
    //
    //     glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID, "u_view"), 1, GL_FALSE, &camera->GetViewMatrix()[0][0]);
    //     glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID, "u_projection"), 1, GL_FALSE, &camera->GetProjectionMatrix()[0][0]);
    //     //    glUniform1f(glGetUniformLocation(ShaderProgramID, "u_time"), elapsedTime.count());
    //
    //     glBindVertexArray(VertexArrayID);
    //     glDrawArrays(GL_TRIANGLES, 0, 6);
    // }

}