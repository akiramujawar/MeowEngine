//
// Created by Akira Mujawar on 11/02/25.
//

#ifndef MEOWENGINE_QUATERNION_HPP
#define MEOWENGINE_QUATERNION_HPP

#include "vector3.hpp"

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
         * In euler angles
         */
        Quaternion(float pX, float pY, float pZ) {}

        Quaternion(const math::Vector3& pEuler) {}

        float W;
        float X;
        float Y;
        float Z;

        [[nodiscard]] float Magnitude() const;
        [[nodiscard]] float MagnitudeSquared() const;

        static float Dot(const Quaternion& pA) {}

        Quaternion Multiply(const Quaternion& pA, const Quaternion& pB) {

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
         */
        void Rotate();
    };

} // MeowEngine

#endif //MEOWENGINE_QUATERNION_HPP
