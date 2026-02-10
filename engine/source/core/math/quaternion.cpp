//
// Created by Akira Mujawar on 11/02/25.
//

#include "quaternion.hpp"
#include "reflection_macro_wrapper.hpp"

namespace MeowEngine {

    void MeowEngine::math::Quaternion::Reflect() {
        REGISTER_PROPERTY(MeowEngine::math::Quaternion, W, float, true, true);
        REGISTER_PROPERTY(MeowEngine::math::Quaternion, X, float, true, true);
        REGISTER_PROPERTY(MeowEngine::math::Quaternion, Y, float, true, true);
        REGISTER_PROPERTY(MeowEngine::math::Quaternion, Z, float, true, true);
    }

    float math::Quaternion::Magnitude() const {
        return AMath::Sqrt(X * X + Y * Y + Z * Z + W * W);
    }

    float math::Quaternion::MagnitudeSquared() const {
        return X * X + Y * Y + Z * Z + W * W;
    }

    void math::Quaternion::Rotate(float pX, float pY, float pZ) {
        Quaternion deltaQuat = Quaternion(pX, pY, pZ);
        Quaternion finalQuat = Quaternion::Multiply(deltaQuat, *this);

        W = finalQuat.W;
        X = finalQuat.X;
        Y = finalQuat.Y;
        Z = finalQuat.Z;
    }

    math::Matrix3x3 math::Quaternion::GetRotationMatrix3x3() {
        float xSquare = X * X;
        float ySquare = Y * Y;
        float zSquare = Z * Z;

        float XY = X * Y;
        float XZ = X * Z;
        float YZ = Y * Z;

        float WX = W * X;
        float WY = W * Y;
        float WZ = W * Z;

        math::Matrix3x3 matrix {};
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

    math::Matrix4x4 math::Quaternion::GetRotationMatrix4x4() {
        float xSquare = X * X;
        float ySquare = Y * Y;
        float zSquare = Z * Z;

        float XY = X * Y;
        float XZ = X * Z;
        float YZ = Y * Z;

        float WX = W * X;
        float WY = W * Y;
        float WZ = W * Z;

        math::Matrix4x4 matrix {};
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

    math::Quaternion math::Quaternion::Normalised() const {
        return math::Quaternion();
    }

    math::Quaternion math::Quaternion::Multiply(const math::Vector3 &pVector) {
        return math::Quaternion();
    }

    void math::Quaternion::Lerp() {

    }

    void math::Quaternion::Slerp() {

    }
} // MeowEngine