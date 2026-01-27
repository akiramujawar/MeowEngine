//
// Created by Akira Mujawar on 26/01/26.
//

#ifndef MEOWENGINE_MATRIX4X4_HPP
#define MEOWENGINE_MATRIX4X4_HPP

namespace MeowEngine::math {
    struct Matrix4x4 {
        static void Reflect();

        float A;
        float B;
        float C;
        float D;

        void Product();
        void Inverse();
        void Determinant();
        void Orthogonal();
        void Transpose();
        static void Identity();
    };
}


#endif //MEOWENGINE_MATRIX4X4_HPP
