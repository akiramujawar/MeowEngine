//
// Created by Akira Mujawar on 11/02/25.
//

#include "quaternion.hpp"
#include "a_math.hpp"

namespace MeowEngine {

    float math::Quaternion::Magnitude() const {
        return AMath::Sqrt(X * X + Y * Y + Z * Z + W * W);
    }

    float math::Quaternion::MagnitudeSquared() const {
        return X * X + Y * Y + Z * Z + W * W;
    }

} // MeowEngine