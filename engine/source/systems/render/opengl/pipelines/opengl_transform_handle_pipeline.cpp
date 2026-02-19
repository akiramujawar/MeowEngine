//
// Created by Akira Mujawar on 18/02/26.
//

#include "opengl_transform_handle_pipeline.hpp"

#include "glm_extension.hpp"

namespace MeowEngine::pipeline {
    OpenGLTransformHandlePipeline::OpenGLTransformHandlePipeline(const GLuint &pShaderProgramID)
            : ShaderProgramID(pShaderProgramID) {
        std::vector<float> vertices;
        std::vector<uint32_t> indices;

        CreateHandle(vertices, indices);
        IndexCount = indices.size();

        glGenVertexArrays(1, &VertexArrayObject);
        glGenBuffers(1, &VertexBufferObject);
        glGenBuffers(1, &ElementBufferObject);

        glBindVertexArray(VertexArrayObject);

        glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER,
                     vertices.size() * sizeof(float),
                     vertices.data(),
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices.size() * sizeof(uint32_t),
                     indices.data(),
                     GL_STATIC_DRAW);

        GLsizei stride = 5 * sizeof(float);

        // positions of generated mesh vertices (location = 0)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                              stride, (void *) 0);

        // axis (location = 1)
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE,
                              stride, (void *) (3 * sizeof(float)));

        // handle types (location = 2)
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE,
                              stride, (void *) (4 * sizeof(float)));

        glBindVertexArray(0);
    }

    OpenGLTransformHandlePipeline::~OpenGLTransformHandlePipeline() {
        glDeleteVertexArrays(1, &VertexArrayObject);
        glDeleteBuffers(1, &VertexArrayObject);
        glDeleteProgram(ShaderProgramID);
    }

    void OpenGLTransformHandlePipeline::Render(
            const MeowEngine::OpenGLAssetManager &assetManager,
            const MeowEngine::entity::TransformHandleComponent *renderComponent,
            const MeowEngine::entity::Transform3DComponent *transform3DComponent,
            const MeowEngine::PerspectiveCamera *camera
    ) const {
        glUseProgram(ShaderProgramID);

        math::Quaternion rotationQuat = transform3DComponent->Quaternion;
        glm::mat4 rotationMatrix = MeowEngine::GLMExtension::GetMat4FromMatrix4x4(
                rotationQuat.GetRotationMatrix4x4());

        glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID, "u_view"), 1, GL_FALSE,
                           &camera->GetViewMatrix()[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID, "u_projection"), 1, GL_FALSE,
                           &camera->GetProjectionMatrix()[0][0]);
        glUniform3fv(glGetUniformLocation(ShaderProgramID, "u_cameraPosition"), 1, &camera->GetPosition()[0]);
        glUniform3fv(glGetUniformLocation(ShaderProgramID, "u_handlePosition"), 1, &transform3DComponent->Position[0]);
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID, "u_handleRotation"), 1, GL_FALSE,
                           &rotationMatrix[0][0]);

        glUniform1f(glGetUniformLocation(ShaderProgramID, "u_handleScale"), 0.11f);
        glUniform1i(glGetUniformLocation(ShaderProgramID, "u_selectedAxis"), -1);

        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindVertexArray(VertexArrayObject);
        glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLTransformHandlePipeline::CreateHandle(
            std::vector<float>& vertices,
            std::vector<uint32_t>& indices) {

        auto addVertex = [&](glm::vec3 pVertexPosition, int pAxis, int pHandleType) {
            vertices.push_back(pVertexPosition.x);
            vertices.push_back(pVertexPosition.y);
            vertices.push_back(pVertexPosition.z);

            vertices.push_back((float) pAxis);
            vertices.push_back((float) pHandleType);

            return (uint32_t) (vertices.size() / 5 - 1);
        };

        for (int axis = 0; axis < 3; axis++) {
            glm::vec3 direction(0.0f);
            direction[axis] = 1.0f;

            AddAxisLines(vertices, indices, addVertex, axis);
            AddScaleCubes(vertices, indices, addVertex, axis, direction);
            AddArrowHeads(vertices, indices, addVertex, axis, direction);
            AddRotationRings(indices, addVertex, axis);
        }
    }

    void OpenGLTransformHandlePipeline::AddAxisLines(
            std::vector<float>& pVertices,
            std::vector<uint32_t>& pIndices,
            const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
            int pAxis
    ) {
        float length = 1.0f;
        float radius = 0.01f;
        int lineSegments = 20;

        uint32_t baseIndex = pVertices.size() / 5;

        for (int i = 0; i < lineSegments; i++) {
            float t = (float)i / (float)lineSegments * glm::two_pi<float>();
            float nextT = (float) (i + 1) / (float)lineSegments * glm::two_pi<float>();

            glm::vec3 p0(0), p1(0), p2(0), p3(0);

            if (pAxis == 0) {
                p0 = {0, cos(t) * radius, sin(t) * radius};
                p1 = {length, cos(t) * radius, sin(t) * radius};
                p2 = {0, cos(nextT) * radius, sin(nextT) * radius};
                p3 = {length, cos(nextT) * radius, sin(nextT) * radius};
            }
            if (pAxis == 1) {
                p0 = {cos(t) * radius, 0, sin(t) * radius};
                p1 = {cos(t) * radius, length, sin(t) * radius};
                p2 = {cos(nextT) * radius, 0, sin(nextT) * radius};
                p3 = {cos(nextT) * radius, length, sin(nextT) * radius};
            }
            if (pAxis == 2) {
                p0 = {cos(t) * radius, sin(t) * radius, 0};
                p1 = {cos(t) * radius, sin(t) * radius, length};
                p2 = {cos(nextT) * radius, sin(nextT) * radius, 0};
                p3 = {cos(nextT) * radius, sin(nextT) * radius, length};
            }

            uint32_t i0 = pAddVertex(p0, pAxis, 0);
            uint32_t i1 = pAddVertex(p1, pAxis, 0);
            uint32_t i2 = pAddVertex(p2, pAxis, 0);
            uint32_t i3 = pAddVertex(p3, pAxis, 0);

            // two triangles per segment
            pIndices.push_back(i0);
            pIndices.push_back(i2);
            pIndices.push_back(i1);

            pIndices.push_back(i1);
            pIndices.push_back(i2);
            pIndices.push_back(i3);
        }
    }

    void OpenGLTransformHandlePipeline::AddScaleCubes(
            std::vector<float>& pVertices,
            std::vector<uint32_t>& pIndices,
            const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
            int pAxis,
            glm::vec3 pDirection
    ) {
        float cubeOffset = 0.5f;
        glm::vec3 cubeCenter = pDirection * cubeOffset;
        float s = 0.05f;

        glm::vec3 offsets[8] = {
                {-s, -s, -s},
                {s,  -s, -s},
                {s,  s,  -s},
                {-s, s,  -s},
                {-s, -s, s},
                {s,  -s, s},
                {s,  s,  s},
                {-s, s,  s}
        };

        uint32_t base = pVertices.size() / 5;

        for (int i = 0; i < 8; i++) {
            pAddVertex(cubeCenter + offsets[i], pAxis, 2);
        }

        uint32_t cubeInd[36] = {
                0, 1, 2, 2, 3, 0,
                4, 5, 6, 6, 7, 4,
                0, 4, 7, 7, 3, 0,
                1, 5, 6, 6, 2, 1,
                3, 2, 6, 6, 7, 3,
                0, 1, 5, 5, 4, 0
        };

        for (int i = 0; i < 36; i++) {
            pIndices.push_back(base + cubeInd[i]);
        }
    }

    void OpenGLTransformHandlePipeline::AddArrowHeads(
            std::vector<float>& pVertices,
            std::vector<uint32_t>& pIndices,
            const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
            int pAxis,
            glm::vec3 pDirection
    ) {
        float arrowOffset = 1.0f;
        float arrowLength = 0.17f;
        float arrowRadius = 0.075f;
        int segments = 16;

        uint32_t arrowBaseIndex = pVertices.size() / 5;

        glm::vec3 tip = pDirection * (arrowOffset + arrowLength);

        // arrow tip
        uint32_t tipIndex = pAddVertex(tip, pAxis, 1);

        // arrow base circle
        for (int i = 0; i < segments; i++) {
            float t = (float) i / (float)segments * glm::two_pi<float>();

            glm::vec3 circle(0);

            if (pAxis == 0) {
                circle = {0, cos(t) * arrowRadius, sin(t) * arrowRadius};
            }

            if (pAxis == 1) {
                circle = {cos(t) * arrowRadius, 0, sin(t) * arrowRadius};
            }

            if (pAxis == 2) {
                circle = {cos(t) * arrowRadius, sin(t) * arrowRadius, 0};
            }

            glm::vec3 basePos = pDirection * arrowOffset + circle;
            pAddVertex(basePos, pAxis, 1);
        }

        // triangles for arrow
        uint32_t baseCircleStart = arrowBaseIndex + 1; // first base vertex
        for (int i = 0; i < segments; i++) {
            uint32_t curr = baseCircleStart + i;
            uint32_t next = baseCircleStart + ((i + 1) % segments);

            // CCW winding
            pIndices.push_back(curr);
            pIndices.push_back(next);
            pIndices.push_back(tipIndex);
        }
    }


    void OpenGLTransformHandlePipeline::AddRotationRings(
            std::vector<uint32_t>& pIndices,
            const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
            int pAxis
    ) {
        float ringRadius = 0.75f;
        float thickness = 0.02f;

        float ringSegments = 64;
        int tubeSegments = 12;

        for (int i = 0; i < ringSegments; i++) {
            float theta = (float) i / ringSegments * glm::two_pi<float>();
            float nextTheta = (float) (i + 1) / ringSegments * glm::two_pi<float>();

            for (int j = 0; j < tubeSegments; j++) {
                float phi = (float) j / (float)tubeSegments * glm::two_pi<float>();
                float nextPhi = (float) (j + 1) / (float)tubeSegments * glm::two_pi<float>();

                auto ringPoint = [&](float theta, float phi) {
                    float R = ringRadius;
                    float r = thickness;

                    // canonical torus around Z axis
                    float x = (R + r * cos(phi)) * cos(theta);
                    float y = (R + r * cos(phi)) * sin(theta);
                    float z = r * sin(phi);

                    glm::vec3 p(x, y, z);

                    // rotate into correct axis
                    if (pAxis == 0) {
                        // rotate 90° around Y
                        p = glm::vec3(p.z, p.y, -p.x);
                    } else if (pAxis == 1) {
                        // rotate -90° around X
                        p = glm::vec3(p.x, p.z, -p.y);
                    }
                    // no rotation needed for Z

                    return p;
                };

                glm::vec3 p0 = ringPoint(theta, phi);
                glm::vec3 p1 = ringPoint(nextTheta, phi);
                glm::vec3 p2 = ringPoint(theta, nextPhi);
                glm::vec3 p3 = ringPoint(nextTheta, nextPhi);

                uint32_t i0 = pAddVertex(p0, pAxis, 3);
                uint32_t i1 = pAddVertex(p1, pAxis, 3);
                uint32_t i2 = pAddVertex(p2, pAxis, 3);
                uint32_t i3 = pAddVertex(p3, pAxis, 3);

                // two triangles per quad
                pIndices.push_back(i0);
                pIndices.push_back(i2);
                pIndices.push_back(i1);

                pIndices.push_back(i1);
                pIndices.push_back(i2);
                pIndices.push_back(i3);
            }
        }
    }
}