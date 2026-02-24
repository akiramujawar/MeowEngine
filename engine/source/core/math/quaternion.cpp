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

    void Quaternion::Rotate(float pX, float pY, float pZ) {
        Quaternion deltaQuat = Quaternion(pX, pY, pZ);
        Quaternion finalQuat = Quaternion::Multiply(deltaQuat, *this);

        W = finalQuat.W;
        X = finalQuat.X;
        Y = finalQuat.Y;
        Z = finalQuat.Z;
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
        // col 1
        matrix.X1 = 1 - 2 * ySquare - 2 * zSquare;
        matrix.X2 = 2 * XY + 2 * WZ;
        matrix.X3 = 2 * XZ - 2 * WY;

        matrix.Y1 = 2 * XY - 2 * WZ;
        matrix.Y2 = 1 - 2 * xSquare - 2 * zSquare;
        matrix.Y3 = 2 * YZ + 2 * WX;

        matrix.Z1 = 2 * XZ + 2 * WY;
        matrix.Z2 = 2 * YZ - 2 * WX;
        matrix.Z3 = 1 - 2 * xSquare - 2 * ySquare;

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
        // col 1
        matrix.X1 = 1 - 2 * ySquare - 2 * zSquare;
        matrix.X2 = 2 * XY + 2 * WZ;
        matrix.X3 = 2 * XZ - 2 * WY;
        matrix.X4 = 0;

        matrix.Y1 = 2 * XY - 2 * WZ;
        matrix.Y2 = 1 - 2 * xSquare - 2 * zSquare;
        matrix.Y3 = 2 * YZ + 2 * WX;
        matrix.Y4 = 0;

        matrix.Z1 = 2 * XZ + 2 * WY;
        matrix.Z2 = 2 * YZ - 2 * WX;
        matrix.Z3 = 1 - 2 * xSquare - 2 * ySquare;
        matrix.Z4 = 0;

        matrix.D1 = 0;
        matrix.D2 = 0;
        matrix.D3 = 0;
        matrix.D4 = 1;

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