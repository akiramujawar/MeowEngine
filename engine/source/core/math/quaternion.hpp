//
// Created by Akira Mujawar on 11/02/25.
//

#ifndef MEOWENGINE_QUATERNION_HPP
#define MEOWENGINE_QUATERNION_HPP

#include "vector3.hpp"
#include "matrix4x4.hpp"
#include "matrix3x3.hpp"
#include "a_math.hpp"

namespace MeowEngine::math {

    struct Quaternion {
        static void Reflect();

        Quaternion()
        : W (0)
        , X (0)
        , Y (0)
        , Z (0) {}

        Quaternion(float pW, float pX, float pY, float pZ)
        : W (pW)
        , X (pX)
        , Y (pY)
        , Z (pZ) {}

        Quaternion(const Quaternion& pQuat)
        : W (pQuat.W)
        , X (pQuat.X)
        , Y (pQuat.Y)
        , Z (pQuat.Z) {}

        /**
         * * We have,
         * q(axis) = cos (angle/2) + axis * sin (angle/2)
         *
         * hence,
         * for each axis angle, we get,
         *
         * axis(x) = cos(Ɵ/2) + sin (Ɵ/2) + 0         + 0
         * axis(y) = cos(φ/2) + 0         + sin (φ/2) + 0
         * axis(z) = cos(⍺/2) + 0         + 0         + sin (⍺/2)
         *
         * doing a matrix multiplication in 3-2-1 format, we get,
         * quat = check the method
         *
         * In euler radians
         *
         * https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles &
         *
         */
        Quaternion(float pX, float pY, float pZ) {
            float cosX = math::AMath::Cos(pX / 2);
            float cosY = math::AMath::Cos(pY / 2);
            float cosZ = math::AMath::Cos(pZ / 2);

            float sinX = math::AMath::Sin(pX / 2);
            float sinY = math::AMath::Sin(pY / 2);
            float sinZ = math::AMath::Sin(pZ / 2);

            // NOTE: Solve this for practice
            W = cosX * cosY * cosZ + sinX * sinY * sinZ;
            X = sinX * cosY * cosZ - cosX * sinY * sinZ;
            Y = cosX * sinY * cosZ + sinX * cosY * sinZ;
            Z = cosX * cosY * sinZ - sinX * sinY * cosZ;
        }

        /**
         * NOTE: check back on this
         * @param pEuler in radians
         */
        explicit Quaternion(const math::Vector3& pEuler) : Quaternion(pEuler.X, pEuler.Y, pEuler.Z) {}

        float W;
        float X;
        float Y;
        float Z;

        // NOTE: this is not required as ||q||
        [[nodiscard]] float Magnitude() const;
        [[nodiscard]] float MagnitudeSquared() const;
        Quaternion Normalised() const;

        /**
         * https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
         * @param pValue
         * @return
         */
        static math::Vector3 Euler(const Quaternion& pValue) {
            float WX = pValue.W * pValue.X;
            float WY = pValue.W * pValue.Y;
            float WZ = pValue.W * pValue.Z;

            float XY = pValue.X * pValue.Y;
            float XZ = pValue.X * pValue.Z;
            float YZ = pValue.Y * pValue.Z;

            float XSquare = pValue.X * pValue.X;
            float YSquare = pValue.Y * pValue.Y;
            float ZSquare = pValue.Z * pValue.Z;

            // x-axis rotation
            float Xpy = 2 * (WX + YZ);
            float Xpx = 1 - 2 * (XSquare + YSquare);

            // y-axis rotation
            float Ypy = math::AMath::Sqrt(1 + 2 * (WY - XZ));
            float Ypx = math::AMath::Sqrt(1 - 2 * (WY - XZ));

            // z-axis rotation
            float Zpy = 2 * (WZ + XY);
            float Zpx = 1 - 2 * (YSquare + ZSquare);

            return {
                math::AMath::ATan2(Xpy, Xpx),
                -(float)M_PI_2 + 2 * math::AMath::ATan2(Ypy, Ypx),
                math::AMath::ATan2(Zpy, Zpx)
            };
        }

        static float Dot(const Quaternion& pA, const Quaternion& pB) {
            return pA.W * pB.W + pA.X * pB.X + pA.Y * pB.Y + pA.Z * pB.Z;
        }

        static Quaternion Multiply(const Quaternion& pA, const Quaternion& pB) {
            return {
                    pA.W * pB.W - pA.X * pB.X - pA.Y * pB.Y - pA.Z * pB.Z,
                    pA.W * pB.X + pA.X * pB.W + pA.Y * pB.Z - pA.Z * pB.Y,
                    pA.W * pB.Y - pA.X * pB.Z + pA.Y * pB.W + pA.Z * pB.X,
                    pA.W * pB.Z + pA.X * pB.Y - pA.Y * pB.X + pA.Z * pB.W
            };
        }

        static Quaternion Multiply(const math::Vector3& pVector);

        /**
         * Conjugate of q = w + vec is q̄ = w - vec
         * @param pQuat
         * @return
         */
        static Quaternion Conjugate(const Quaternion& pQuat) {
            return {
                pQuat.W,
                -pQuat.X,
                -pQuat.Y,
                -pQuat.Z
            };
        }

        /**
         * q⁻¹ = q̄ / q² - less calculations
         * or
         * q⁻¹ = q * unit diagonal matrix
         * @param pQuat
         * @return
         */
        static Quaternion Inverse(const Quaternion& pQuat) {
            Quaternion conjugate = Quaternion::Conjugate(pQuat);
            float magnitude = pQuat.MagnitudeSquared();

            return {
                conjugate.W / magnitude,
                conjugate.X / magnitude,
                conjugate.Y / magnitude,
                conjugate.Z / magnitude
            };
        }

        /**
         * Homomorphism
         *
         * Ideas
         * - convert euler to quat and multiple that quat to existing quat
         * - quat * euler to quat * quat inverse - as per formula - homomorphism
         * - vec = v + st + q x t ; t = 2q x v; vector to vector rotation by applying pair of relations
         */
        void Rotate(float pX, float pY, float pZ);

        math::Matrix3x3 GetRotationMatrix3x3();
        math::Matrix4x4 GetRotationMatrix4x4();

        void Lerp();
        void Slerp();
    };

} // MeowEngine

#endif //MEOWENGINE_QUATERNION_HPP
