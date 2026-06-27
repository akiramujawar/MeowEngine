//
// Created by Akira Mujawar on 26/01/26.
//

#ifndef MEOWENGINE_MATRIX4X4_HPP
#define MEOWENGINE_MATRIX4X4_HPP

#include "GLM_API.hpp"

namespace MeowEngine::Core::Math {

    struct Matrix4x4 {
        static void Reflect();

        float X1, X2, X3, X4;
        float Y1, Y2, Y3, Y4;
        float Z1, Z2, Z3, Z4;
        float D1, D2, D3, D4;

        void Product();
        void Inverse();
        void Determinant();
        void Orthogonal();
        void Transpose();

        static Matrix4x4 Identity();

        std::string GetString() const {
            return  "X1"+std::to_string(X1)+", X2"+std::to_string(X2)+", X3"+std::to_string(X3)+", X4"+std::to_string(X4)+"\n" +
                    "Y1"+std::to_string(Y1)+", Y2"+std::to_string(Y2)+", Y3"+std::to_string(Y3)+", Y4"+std::to_string(Y4)+"\n" +
                    "Z1"+std::to_string(Z1)+", Z2"+std::to_string(Z2)+", Z3"+std::to_string(Z3)+", Z4"+std::to_string(Z4)+"\n" +
                    "D1"+std::to_string(D1)+", D2"+std::to_string(D2)+", D3"+std::to_string(D3)+", D4"+std::to_string(D4)+"\n";
        }


        // -- GLM ------------------------
        static Matrix4x4 Matrix4X4FromGlm(const glm::mat4 value) {
            Matrix4x4 matrix {};

            matrix.X1 = value[0][0];
            matrix.X2 = value[0][1];
            matrix.X3 = value[0][2];
            matrix.X4 = value[0][3];

            matrix.Y1 = value[1][0];
            matrix.Y2 = value[1][1];
            matrix.Y3 = value[1][2];
            matrix.Y4 = value[1][3];

            matrix.Z1 = value[2][0];
            matrix.Z2 = value[2][1];
            matrix.Z3 = value[2][2];
            matrix.Z4 = value[2][3];

            matrix.D1 = value[3][0];
            matrix.D2 = value[3][1];
            matrix.D3 = value[3][2];
            matrix.D4 = value[3][3];

            return matrix;
        }

        static glm::mat4 GlmFromMatrix4x4(const Matrix4x4 pValue) {
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


#endif //MEOWENGINE_MATRIX4X4_HPP
