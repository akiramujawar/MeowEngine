//
// Created by Akira Mujawar on 11/02/25.
//

#include "quaternion.hpp"
#include "reflection_macro_wrapper.hpp"

namespace MeowEngine::Core::Math {

    void Quaternion::Reflect() {
        REGISTER_PROPERTY(Quaternion, W, float, true, true);
        REGISTER_PROPERTY(Quaternion, X, float, true, true);
        REGISTER_PROPERTY(Quaternion, Y, float, true, true);
        REGISTER_PROPERTY(Quaternion, Z, float, true, true);
    }

    float Quaternion::Magnitude() const {
        return Math::Sqrt(X * X + Y * Y + Z * Z + W * W);
    }

    float Quaternion::MagnitudeSquared() const {
        return X * X + Y * Y + Z * Z + W * W;
    }

    Quaternion Quaternion::RotateByEuler(float pX, float pY, float pZ) const {
        Quaternion deltaQuat = Quaternion(pX, pY, pZ);
        Quaternion finalQuat = Multiply(deltaQuat, *this);

        return finalQuat;
    }

    Quaternion Quaternion::RotateByEuler(const Vector3& euler) const {
        return RotateByEuler(euler.X, euler.Y, euler.Z);
    }

    Vector3 Quaternion::RotateAroundAxis(const Vector3& value) const {
        Quaternion axisQuat = Quaternion(0, value.X, value.Y, value.Z);
        Quaternion a = Multiply(*this, axisQuat);
        Quaternion b = Multiply(a, Inverse(*this));

        return Vector3(b.X, b.Y, b.Z);
    }

    Quaternion Quaternion::Normalised() {
        float length = Magnitude();

        // Edge Case we return identity quat
        if(length == 0) {
            return Quaternion::Identity();
        };

        W = W / length;
        X = X / length;
        Y = Y / length;
        Z = Z / length;

        return {
            W,
            X,
            Y,
            Z
        };
    }
//
//    math::Quaternion math::Quaternion::Multiply(const math::Vector3 &pVector) {
//        return math::Quaternion();
//    }
//
//    void math::Quaternion::Lerp() {
//
//    }
//
//    void math::Quaternion::Slerp() {
//
//    }
} // MeowEngine