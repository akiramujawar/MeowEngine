//
// Created by Akira Mujawar on 26/06/26.
//

#include "MatrixClip.hpp"

namespace MeowEngine::Core::Math {
    Matrix4x4 MatrixClip::Perspective(float fov, float aspect, float near, float far) {
        auto matrix = glm::perspectiveRH_NO(fov, aspect, near, far);

        return Matrix4x4::Matrix4X4FromGlm(matrix);
    }
}
