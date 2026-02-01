//
// Created by Akira Mujawar on 27/01/26.
//

#ifndef MEOWENGINE_MATRIX3X3_HPP
#define MEOWENGINE_MATRIX3X3_HPP

namespace MeowEngine::math {

    struct Matrix3x3 {
        static void Reflect();

        float X1, X2, X3;
        float Y1, Y2, Y3;
        float Z1, Z2, Z3;
    };
}


#endif //MEOWENGINE_MATRIX3X3_HPP
