//
// Created by Akira Mujawar on 26/06/26.
//

#ifndef MEOWENGINE_MATRIXCLIP_HPP
#define MEOWENGINE_MATRIXCLIP_HPP

#include "Matrix.hpp"

namespace MeowEngine::Core::Math {
    struct MatrixClip {
    public:
        static Matrix4x4 PerspectiveLH_NO(float fov, float aspect, float near, float far) {
            auto matrix = glm::perspectiveLH_NO(fov, aspect, near, far);

            return Matrix4x4::Matrix4X4FromGlm(matrix);
        }
    };
}

class MatrixClip {};


#endif //MEOWENGINE_MATRIXCLIP_HPP