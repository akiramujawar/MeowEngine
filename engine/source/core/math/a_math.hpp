//
// Created by Akira Mujawar on 27/01/26.
//

#ifndef MEOWENGINE_A_MATH_HPP
#define MEOWENGINE_A_MATH_HPP

#include "cmath"

namespace MeowEngine::math {

    /**
     * A stands for Algebra. Hence AMath.
     * There's absolutely no need to have this, but for library sake, we create a wrapper methods
     */
    class AMath {
        // sin
        // cos
        // tan etc...

    public:
        static float Sqrt(float pValue) {
            return sqrt(pValue);
        }
    };

}


#endif //MEOWENGINE_A_MATH_HPP
