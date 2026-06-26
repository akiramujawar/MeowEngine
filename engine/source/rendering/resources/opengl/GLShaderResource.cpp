//
// Created by Akira Mujawar on 20/05/26.
//

#include "GLShaderResource.hpp"

#include <cstdlib>
#include "GL_API.hpp"

#include "AssetManager.hpp"
#include "MeowService.hpp"

namespace MeowEngine::Rendering {
    GLShaderResource::GLShaderResource(Asset::AssetHandle handle) {
        auto* asset = MeowService().AssetManager.GetAsset<Asset::ShaderAsset>(handle);

#ifdef USING_GLES
        MeowEngine::Log(logTag, "#version 300 es") ;
        std::string vertexShaderSource {"#version 300 es\nprecision mediump float;\n" + asset->VertexSource};
        std::string fragmentShaderSource{"#version 300 es\nprecision mediump float;\n" + asset->FragmentSource};
#else
        //        std::string vertexShaderSource {"#version 140\n" + vertexShaderCode};
        //        std::string fragmentShaderSource{"#version 140\n" + fragmentShaderCode};
        std::string vertexShaderSource {"#version 330 core\n" + asset->VertexSource};
        std::string fragmentShaderSource{"#version 330 core\n" + asset->FragmentSource};
        //        std::string vertexShaderSource {vertexShaderCode};
        //        std::string fragmentShaderSource{fragmentShaderCode};
#endif

        // Compile fragment and vertex shader from our compiler (method)
        GLuint shaderProgramId {glCreateProgram()};
        GLuint vertexShaderId {Compile(GL_VERTEX_SHADER, vertexShaderSource)};
        GLuint fragmentShaderId {Compile(GL_FRAGMENT_SHADER, fragmentShaderSource)};

        glAttachShader(shaderProgramId, vertexShaderId);
        glAttachShader(shaderProgramId, fragmentShaderId);
        glLinkProgram(shaderProgramId);

        // Link Shader
        GLint shaderProgramLinkResult;
        glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &shaderProgramLinkResult);

        // Check the if our shader was successfully linked
        if(!shaderProgramLinkResult) {
            GLint errorMessageLength;
            glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &errorMessageLength);
            std::vector<char> errorMessage(errorMessageLength + 1);
            glGetProgramInfoLog(shaderProgramId, errorMessageLength, nullptr, &errorMessage[0]);
            MeowEngine::Log("GLShaderResource::Constructed", &errorMessage[0]);

            throw std::runtime_error("GLShaderResource::Constructed, Shader Program failed to compile");
        }

        // It's important to detach shader from that way deleting shader free's the memory
        glDetachShader(shaderProgramId, vertexShaderId);
        glDetachShader(shaderProgramId, fragmentShaderId);

        // Clean up shader as they are no longer needed after linking
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        ID = shaderProgramId;
    }

    std::uint32_t GLShaderResource::Compile(const std::uint32_t& shaderType, const std::string& shaderSource) {
        GLuint shaderId{glCreateShader(shaderType)};

        const char* shaderData{shaderSource.c_str()};
        glShaderSource(shaderId, 1, &shaderData, nullptr);
        glCompileShader(shaderId);

        GLint shaderCompilationResult;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompilationResult);

        if(!shaderCompilationResult) {
            GLint errorMessageLength;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &errorMessageLength);
            std::vector<char> errorMessage(errorMessageLength + 1);
            glGetShaderInfoLog(shaderId, errorMessageLength, nullptr, &errorMessage[0]);
            MeowEngine::Log("OpenGLPipeline::CompileShader", &errorMessage[0]);

            throw std::runtime_error("GLShaderResource::Compile, Shader failed to compile");
        }

        return shaderId;
    }
}
