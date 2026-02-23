//
// Created by Akira Mujawar on 13/02/25.
//

#include "opengl_box_collider.hpp"

namespace MeowEngine {


    OpenGLBoxCollider::OpenGLBoxCollider() {
        // xyz
        float vertices[] = {
                -1, -1, -1,  1, -1, -1,  1,  1, -1,  -1,  1, -1, // Back face
                -1, -1,  1,  1, -1,  1,  1,  1,  1,  -1,  1,  1, // Front face
                -1, -1, -1, -1,  1, -1, -1,  1,  1,  -1, -1,  1, // Left face
                1, -1, -1,  1,  1, -1,  1,  1,  1,   1, -1,  1, // Right face
                -1,  1, -1,  1,  1, -1,  1,  1,  1,  -1,  1,  1, // Top face
                -1, -1, -1,  1, -1, -1,  1, -1,  1,  -1, -1,  1  // Bottom face
        };
        // trinagle
        unsigned int indices[] = {
                0, 1, 2,  2, 3, 0,  // Back face
                4, 5, 6,  6, 7, 4,  // Front face
                8, 9, 10, 10, 11, 8, // Left face
                12,13,14, 14,15,12, // Right face
                16,17,18, 18,19,16, // Top face
                20,21,22, 22,23,20  // Bottom face
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // dynamic instances
        glGenBuffers(1, &instanceVBO);
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

        for(int i = 0 ; i < 4; i++) {
            glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
            glEnableVertexAttribArray(1 + i);

            glVertexAttribDivisor(1 + i, 1);
        }

        glBindVertexArray(0);
    }

    OpenGLBoxCollider::~OpenGLBoxCollider() {

    }

    void OpenGLBoxCollider::Draw(const std::vector<glm::mat4>& colliders) {
        // NOTE: We render everything in the scene and with
        //  no occlusion / lods hence forth for a primary versions this would be acceptable
        glBindVertexArray(VAO);

        // NOTE: need to recheck this as layout in shader doesn't work for web builds
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        if(!colliders.empty()) {
            glBufferData(GL_ARRAY_BUFFER, colliders.size() * sizeof(glm::mat4), colliders.data(), GL_DYNAMIC_DRAW);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, colliders.size());
#ifndef USING_GLES
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
        glBindVertexArray(0);
    }

} // MeowEngine