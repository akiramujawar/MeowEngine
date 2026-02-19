//
// Created by Akira Mujawar on 19/02/26.
//

#ifndef MEOWENGINE_OPENGL_EXTENSION_HPP
#define MEOWENGINE_OPENGL_EXTENSION_HPP

#include "glm_wrapper.hpp"
#include "math_wrapper.hpp"

namespace MeowEngine {
    class OpenGLExtension {
    public:
        /**
         * TODO: Implement full matrix structure for transform matrix
         * @param pValue
         * @return
         */
        static glm::mat4 GetMat4FromMatrix4x4(const math::Matrix4x4 pValue) {
            glm::mat4 rotation4Matrix {};

            rotation4Matrix[0][0] = pValue.X1;
            rotation4Matrix[0][1] = pValue.X2;
            rotation4Matrix[0][2] = pValue.X3;
            rotation4Matrix[0][3] = pValue.X4;

            rotation4Matrix[1][0] = pValue.Y1;
            rotation4Matrix[1][1] = pValue.Y2;
            rotation4Matrix[1][2] = pValue.Y3;
            rotation4Matrix[1][3] = pValue.Y4;

            rotation4Matrix[2][0] = pValue.Z1;
            rotation4Matrix[2][1] = pValue.Z2;
            rotation4Matrix[2][2] = pValue.Z3;
            rotation4Matrix[2][3] = pValue.Z4;

            rotation4Matrix[3][0] = pValue.D1;
            rotation4Matrix[3][1] = pValue.D2;
            rotation4Matrix[3][2] = pValue.D3;
            rotation4Matrix[3][3] = pValue.D4;

            return rotation4Matrix;
        }
    };
}


#endif //MEOWENGINE_OPENGL_EXTENSION_HPP
