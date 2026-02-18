//
// Created by Akira Mujawar on 18/02/26.
//

#include "opengl_transform_handle_pipeline.hpp"

using MeowEngine::pipeline::OpenGLTransformHandlePipeline;

OpenGLTransformHandlePipeline::OpenGLTransformHandlePipeline(const GLuint &pShaderProgramID)
: ShaderProgramID(pShaderProgramID) {
    glGenVertexArrays(1, &VertexArrayObject);
    glGenBuffers(1, &VertexArrayObject);
}

OpenGLTransformHandlePipeline::~OpenGLTransformHandlePipeline() {
    glDeleteVertexArrays(1, &VertexArrayObject);
    glDeleteBuffers(1, &VertexArrayObject);
    glDeleteProgram(ShaderProgramID);
}

void OpenGLTransformHandlePipeline::Render(
    const MeowEngine::OpenGLAssetManager& assetManager,
    const MeowEngine::entity::TransformHandleComponent* renderComponent,
    const MeowEngine::entity::Transform3DComponent* transform3DComponent,
    const MeowEngine::PerspectiveCamera* camera
) const {
    glUseProgram(ShaderProgramID);

    glBindVertexArray(VertexArrayObject);
    glDrawElements(GL_TRIANGLES, 10000, GL_UNSIGNED_INT, 0);
}
