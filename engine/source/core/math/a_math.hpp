//
// Created by Akira Mujawar on 27/01/26.
//

#ifndef MEOWENGINE_A_MATH_HPP
#define MEOWENGINE_A_MATH_HPP

#include "cmath"

namespace MeowEngine::Core::Math {

    inline float Sin(float p) { return std::sin(p); }
    inline float Sin(double p) { return std::sin(p); }

    inline float Cos(float p) { return std::cos(p); }
    inline float Cos(double p) { return std::cos(p); }

    inline float Tan(float p) { return std::tan(p); }
    inline float Tan(double p) { return std::tan(p); }

    inline float ASin(float p) { return std::asin(p); }
    inline float ASin(double p) { return std::asin(p); }

    inline float ACos(float p) { return std::acos(p); }
    inline float ACos(double p) { return std::acos(p); }

    inline float ATan(float p) { return std::atan(p); }
    inline float ATan(double p) { return std::atan(p); }

    inline float ATan2(float pY, float pX) { return std::atan2(pY, pX); }
    inline float ATan2(double pY, double pX) { return std::atan2(pY, pX); }

    inline float Sqrt(float p) { return std::sqrt(p); }
    inline float Sqrt(double p) { return std::sqrt(p); }

}


#endif //MEOWENGINE_A_MATH_HPP
