//
// Created by Akira Mujawar on 13/07/24.
//

#include "vector3.hpp"
#include "reflection_macro_wrapper.hpp"
#include "math_wrapper.hpp"

void MeowEngine::math::Vector3::Reflect() {
    REGISTER_PROPERTY(MeowEngine::math::Vector3, X, float, true);
    REGISTER_PROPERTY(MeowEngine::math::Vector3, Y, float, true);
    REGISTER_PROPERTY(MeowEngine::math::Vector3, Z, float, true);
}

float MeowEngine::math::Vector3::Magnitude() const {
    return sqrt(X * X + Y * Y + Z * Z);
}

float MeowEngine::math::Vector3::MagnitudeSquared() const {
    return X * X + Y * Y + Z * Z;
}

MeowEngine::math::Vector3 MeowEngine::math::Vector3::Normalized() const {
    float length = Magnitude();
    return {
        X / length,
        Y / length,
        Z / length
    };
}

MeowEngine::math::Vector3 MeowEngine::math::Vector3::ProjectOn(const Vector3 &in) const {
    float lengthSquareOfGivenVector = in.MagnitudeSquared();
    float dot = Vector3::Dot(*this, in);

    // length of adjacent side to angle is :- ||a||*cos(angle) = dot / length
    float lengthOfProjection = dot / lengthSquareOfGivenVector;

    return {
        in.X * lengthOfProjection,
        in.Y * lengthOfProjection,
        in.Z * lengthOfProjection
    };
}

MeowEngine::math::Vector3 MeowEngine::math::Vector3::PerpendicularToProjection(const Vector3 &in) const {
    return *this - ProjectOn(in);
}
