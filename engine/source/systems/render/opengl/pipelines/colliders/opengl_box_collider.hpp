//
// Created by Akira Mujawar on 13/02/25.
//

#ifndef MEOWENGINE_OPENGL_BOX_COLLIDER_HPP
#define MEOWENGINE_OPENGL_BOX_COLLIDER_HPP

#include "graphics_wrapper.hpp"
#include "glm_wrapper.hpp"
#include "vector"

namespace MeowEngine {
    /**
     * Draws a boundary collider for box types. Is handled by OpenGLColliderPipeline
     */
    struct OpenGLBoxCollider {
        OpenGLBoxCollider();
        ~OpenGLBoxCollider();

    public:
        void Draw(const std::vector<glm::mat4>& colliders);

    private:
        unsigned int VAO; // vertex array object (the sequence of VB0)
        unsigned int VBO; // vertex buffer object (positions / normals / uvs / colours)
        unsigned int EBO; // element buffer object (index list for drawing triangles)
        unsigned int instanceVBO; // optimization to draw same type mesh -- instance rendering
    };

} // MeowEngine

#endif //MEOWENGINE_OPENGL_BOX_COLLIDER_HPP
