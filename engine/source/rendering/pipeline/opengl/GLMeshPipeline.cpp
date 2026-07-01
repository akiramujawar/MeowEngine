//
// Created by Akira Mujawar on 23/06/24.
//

#include "GLMeshPipeline.hpp"

//#include "opengl_pipeline_base.hpp"
// #include "AssetLoader.hpp"
// #include "opengl_asset_manager.hpp"
// #include <stdexcept>
//#include <vector>

#include <log.hpp>
#include <GL_API.hpp>
#include <RenderContext.hpp>
#include <RenderResourceManager.hpp>
#include <GLShaderResource.hpp>
#include "MeshDrawData.hpp"


namespace MeowEngine::Rendering {
    GLMeshPipeline::GLMeshPipeline() {
        Stride = 5 * sizeof (float);
        OffsetPosition = 0 ;
        OffsetTextureCoord = 3 * sizeof(float);
    }

    void GLMeshPipeline::Draw(const RenderContext& context, const MeshDrawData& data) {
        if (!data.Shader.IsValid()) {
            return;
        }

        const auto& shader = context.ResourceManager->GetShaderResource(data.Shader);
        const auto& mesh = context.ResourceManager->GetMeshResource(data.Mesh);
        const auto& texture = context.ResourceManager->GetTextureResource(data.Texture);

        if (!IsInitialized) {
            IsInitialized = true;

            UniformLocationMVP = glGetUniformLocation(shader.GetID(), "u_mvp");
            AttributeLocationVertexPosition = glGetAttribLocation(shader.GetID(), "a_vertexPosition");
            AttributeLocationTextureCoord = glGetAttribLocation(shader.GetID(), "a_textureCoord");
        }

        glUseProgram(shader.GetID());

        // const MeowEngine::StaticMeshInstance& staticMeshInstance = meshRenderComponent->GetMeshInstance();
        // const Rendering::GLMeshResource& mesh = assetManager.GetStaticMesh(staticMeshInstance.GetMesh());
        //
        // glUseProgram(ShaderProgramID);
        glBindVertexArray(mesh.GetVertexArrayId());

        // // This will render a wire frame for us :)
        // // n just like that we can have a wire frame mode (not that i need it but yeah lol)
        // #ifndef USING_GLES
        //     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // #endif

        // Activating our vertex position attribute
        glEnableVertexAttribArray(AttributeLocationVertexPosition);

        // Activate our texture coord attribute
        glEnableVertexAttribArray(AttributeLocationTextureCoord);
        // end - Activate Shader Program - finish

        // Populating our MVP in shader program
        glUniformMatrix4fv(UniformLocationMVP, 1, GL_FALSE, &data.TransformMatrix[0][0]);

        // Apply the texture we want to paint the mesh with.
        texture.Bind();

        // Bind the vertex and index buffers
        glBindBuffer(GL_ARRAY_BUFFER, mesh.GetVertexBufferId());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexBufferId());

        // Configuring the vertex position attribute
        glVertexAttribPointer(
                AttributeLocationVertexPosition,
                3,
                GL_FLOAT,
                GL_FALSE,
                Stride,
                reinterpret_cast<const GLvoid*>(OffsetPosition) // (GLvoid*)(OffsetPosition) -> had warnings
        );

        // Config the texture coord
        glVertexAttribPointer(
                AttributeLocationTextureCoord,
                2,
                GL_FLOAT,
                GL_FALSE,
                Stride,
                reinterpret_cast<const GLvoid*>(OffsetTextureCoord) // (GLvoid*)(OffsetTextureCoord) -> had warnings
        );

        // Draw command providing the total number of vertices from mesh
        glDrawElements(
                GL_TRIANGLES,
                mesh.GetNumIndices(),
                GL_UNSIGNED_INT,
                reinterpret_cast<const GLvoid*>(0) // (GLvoid*)(0)
        );

        // // This will render a wire frame for us :)
        // // n just like that we can have a wire frame mode (not that i need it but yeah lol)
        // #ifndef USING_GLES
        //     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // #endif

        // Disabling the vertex position attribute as we are done using it. (seems like file open - close streaming process)
        glDisableVertexAttribArray(AttributeLocationVertexPosition);
        glDisableVertexAttribArray(AttributeLocationTextureCoord);
    }
}