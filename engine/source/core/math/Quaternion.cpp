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

    Matrix3x3 Quaternion::GetRotationMatrix3x3() {
        float xSquare = X * X;
        float ySquare = Y * Y;
        float zSquare = Z * Z;

        float XY = X * Y;
        float XZ = X * Z;
        float YZ = Y * Z;

        float WX = W * X;
        float WY = W * Y;
        float WZ = W * Z;

        Matrix3x3 matrix {};

        matrix[0][0] = 1 - 2 * ySquare - 2 * zSquare;
        matrix[1][0] = 2 * XY + 2 * WZ;
        matrix[2][0] = 2 * XZ - 2 * WY;

        matrix[0][1] = 2 * XY - 2 * WZ;
        matrix[1][1] = 1 - 2 * xSquare - 2 * zSquare;
        matrix[2][1] = 2 * YZ + 2 * WX;

        matrix[0][2] = 2 * XZ + 2 * WY;
        matrix[1][2] = 2 * YZ - 2 * WX;
        matrix[2][2] = 1 - 2 * xSquare - 2 * ySquare;

        return matrix;
    }

    Matrix4x4 Quaternion::GetRotationMatrix4x4() {
        float xSquare = X * X;
        float ySquare = Y * Y;
        float zSquare = Z * Z;

        float XY = X * Y;
        float XZ = X * Z;
        float YZ = Y * Z;

        float WX = W * X;
        float WY = W * Y;
        float WZ = W * Z;

        Matrix4x4 matrix {};

        matrix[0][0] = 1 - 2 * ySquare - 2 * zSquare;
        matrix[1][0] = 2 * XY + 2 * WZ;
        matrix[2][0] = 2 * XZ - 2 * WY;
        matrix[3][0] = 0;

        matrix[0][1] = 2 * XY - 2 * WZ;
        matrix[1][1] = 1 - 2 * xSquare - 2 * zSquare;
        matrix[2][1] = 2 * YZ + 2 * WX;
        matrix[3][1] = 0;

        matrix[0][2] = 2 * XZ + 2 * WY;
        matrix[1][2] = 2 * YZ - 2 * WX;
        matrix[2][2] = 1 - 2 * xSquare - 2 * ySquare;
        matrix[3][2] = 0;

        matrix[0][3] = 0;
        matrix[1][3] = 0;
        matrix[2][3] = 0;
        matrix[3][3] = 1;

        return matrix;
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