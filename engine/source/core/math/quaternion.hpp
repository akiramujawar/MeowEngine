//
// Created by Akira Mujawar on 11/02/25.
//

#ifndef MEOWENGINE_QUATERNION_HPP
#define MEOWENGINE_QUATERNION_HPP

#include "vector3.hpp"
#include "matrix4x4.hpp"
#include "matrix3x3.hpp"
#include "a_math.hpp"
#include "m_object.hpp"

namespace MeowEngine::math {

    struct Quaternion : entity::MObject {
        REFLECT_MObject(Quaternion)
        static void Reflect();
        std::string ToString() const {
            return
                std::to_string(W) + ", " +
                std::to_string(X) + ", " +
                std::to_string(Y) + ", " +
                std::to_string(Z);
        }

        Quaternion()
        : W (1)
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
            pX *= M_PI / 180;
            pY *= M_PI / 180;
            pZ *= M_PI / 180;

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

        float& operator[](int index) {
            switch (index) {
                case 0: return W;
                case 1: return X;
                case 2: return Y;
                case 3: return Z;
                default: return X;
            }
        }

        // NOTE: this is not required as ||q||
        [[nodiscard]] float Magnitude() const;
        [[nodiscard]] float MagnitudeSquared() const;
        Quaternion Normalised();

        /**
         * https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
         * @param pValue
         * @return
         */
        static math::Vector3 Euler(const Quaternion& pValue) {
            Quaternion quat = pValue;
            quat.Normalised();

            float WX = quat.W * quat.X;
            float WY = quat.W * quat.Y;
            float WZ = quat.W * quat.Z;

            float XY = quat.X * quat.Y;
            float XZ = quat.X * quat.Z;
            float YZ = quat.Y * quat.Z;

            float XSquare = quat.X * quat.X;
            float YSquare = quat.Y * quat.Y;
            float ZSquare = quat.Z * quat.Z;

            // x-axis rotation (roll)
            float Xpy = 2 * (WX + YZ);
            float Xpx = 1 - 2 * (XSquare + YSquare);

            // y-axis rotation (pitch)
//            float Ypy = math::AMath::Sqrt(1 + 2 * (WY - XZ));
//            float Ypx = math::AMath::Sqrt(1 - 2 * (WY - XZ));
            float Sinp = 2.0f * (WY - XZ);
            if (Sinp > 1.0f) {
                Sinp = 1.0f;
            }
            if (Sinp < -1.0f) {
                Sinp = -1.0f;
            }

            // z-axis rotation (yaw)
            float Zpy = 2 * (WZ + XY);
            float Zpx = 1 - 2 * (YSquare + ZSquare);

            float XRadian = math::AMath::ATan2(Xpy, Xpx);
            float YRadian = math::AMath::ASin(Sinp);
            float ZRadian = math::AMath::ATan2(Zpy, Zpx);

            return {
                static_cast<float>(XRadian * 180 / M_PI),
                static_cast<float>(YRadian * 180 / M_PI),
                static_cast<float>(ZRadian * 180 / M_PI)
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

        static Quaternion Identity() {
            return {1,0,0,0};
        }
    };

} // MeowEngine

#endif //MEOWENGINE_QUATERNION_HPP
