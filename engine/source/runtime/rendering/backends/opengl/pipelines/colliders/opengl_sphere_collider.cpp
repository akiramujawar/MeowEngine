//
// Created by Akira Mujawar on 13/02/25.
//

#include "opengl_sphere_collider.hpp"
#include "math_wrapper.hpp"

namespace MeowEngine {
    OpenGLSphereCollider::OpenGLSphereCollider() {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        int segmentCountForCircles = 24;

        // 3 circles to be drawn on different planes
        for(int i = 0 ; i < 3; i++){
            int startIndex = vertices.size() / 3;

            // segments for each circle (we keep 12 as a optimal value)
            for(int j = 0; j < segmentCountForCircles; j++){
                float angle = (float)j / segmentCountForCircles * M_PI * 2.0f;
                float cos = std::cos(angle);
                float sin = std::sin(angle);

                switch (i) {
                    case 0:
                        vertices.insert(vertices.end(), {cos, sin, 0});
                        break;
                    case 1:
                        vertices.insert(vertices.end(), {cos, 0, sin});
                        break;
                    case 2:
                        vertices.insert(vertices.end(), {0, cos, sin});
                        break;
                }

                indices.push_back(startIndex + j);
                indices.push_back(startIndex + (j + 1) % segmentCountForCircles);
            }
        }

        indicesCount = indices.size();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // dynamic instances
        glGenBuffers(1, &instanceVBO);
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

        for(int i = 0; i < 4; i++){
            glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
            glEnableVertexAttribArray(1 + i);

            glVertexAttribDivisor(1 + i, 1);
        }

        glBindVertexArray(0);
    }

    OpenGLSphereCollider::~OpenGLSphereCollider() {}

    void OpenGLSphereCollider::Draw(const std::vector<glm::mat4> &colliders) {
        // NOTE: We render everything in the scene and with
        //  no occlusion / lods hence forth for a primary versions this would be acceptable
        glBindVertexArray(VAO);

        // NOTE: need to recheck this as layout in shader doesn't work for web builds
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        if(!colliders.empty()) {
            glBufferData(GL_ARRAY_BUFFER, colliders.size() * sizeof(glm::mat4), colliders.data(), GL_DYNAMIC_DRAW);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawElementsInstanced(GL_LINES, indicesCount, GL_UNSIGNED_INT, 0, colliders.size());
#ifndef USING_GLES
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
        glBindVertexArray(0);
    }

} // MeowEngine