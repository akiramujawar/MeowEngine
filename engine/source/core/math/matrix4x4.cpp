//
// Created by Akira Mujawar on 26/01/26.
//

#include "matrix4x4.hpp"

namespace MeowEngine::Core::Math {

    void Matrix4x4::Reflect() {

    }

    Matrix4x4 Matrix4x4::Identity() {
        glm::mat4 identity = glm::mat4(1.0f);
        return Matrix4X4FromGlm(identity);
    }
}
