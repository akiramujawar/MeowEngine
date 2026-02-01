//
// Created by Akira Mujawar on 26/01/26.
//

#ifndef MEOWENGINE_MATRIX4X4_HPP
#define MEOWENGINE_MATRIX4X4_HPP

namespace MeowEngine::math {
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
        static void Identity();
    };
}


#endif //MEOWENGINE_MATRIX4X4_HPP
