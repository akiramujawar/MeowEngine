//
// Created by Akira Mujawar on 13/07/24.
//

#ifndef MEOWENGINE_VECTOR3_HPP
#define MEOWENGINE_VECTOR3_HPP

namespace MeowEngine::math {
    struct Vector3 {
        static void Reflect();

        Vector3()
        : X (0)
        , Y (0)
        , Z (0) {}

        Vector3(float x, float y, float z)
        : X (x)
        , Y (y)
        , Z (z) {}

        float X;
        float Y;
        float Z;

        // allows us to something like vec[1] = 2 instead of vec.y = 2
        float& operator[](int index) {
            switch (index) {
                case 0: return X;
                case 1: return Y;
                case 2: return Z;
                default: return X;
            }
        }

        const float& operator[](int index) const {
            switch (index) {
                case 0: return X;
                case 1: return Y;
                case 2: return Z;
                default: return X;
            }
        }

        Vector3 operator-(const Vector3& in) const {
            return {
                X - in.X,
                Y - in.Y,
                Z - in.Z
            };
        }

        Vector3 operator+(const Vector3& in) const {
            return {
                X + in.X,
                Y + in.Y,
                Z + in.Z
            };
        }

        Vector3 operator*(const float in) const {
            return {
                X * in,
                Y * in,
                Z * in
            };
        }

        Vector3 operator/(const float in) const {
            return {
                X / in,
                Y / in,
                Z / in
            };
        }

        /**
         * Scalar product determining the directions
         * also can be dot = ||a|| * ||b|| * cos(angle)
         * +ve value is same direction
         * -ve value is opposite direction
         * 0 are orthogonal
         * @param pA
         * @param pB
         * @return
         */
        static float Dot(const Vector3& pA,const Vector3& pB) {
            return pA.X * pB.X + pA.Y * pB.Y + pA.Z * pB.Z;
        }

        /**
         * Vector product returning a vector perpendicular to given vectors
         * e.g. like a 2 points on plane and a normal to the plane
         * also can be cross = ||a|| * ||b|| * sin(angle)
         * @param pA
         * @param pB
         * @return
         */
        static Vector3 Cross(const Vector3& pA, const Vector3& pB) {
            return {
                pA.Y * pB.Z - pA.Z * pB.Y,
                - pA.X * pB.Z + pA.Z * pB.X,
                pA.X * pB.Y - pA.Y * pB.X
            };
        }

        /**
         * Magnitude is length of vector ||vec|| = square root (x*x + y*y + z*z);
         * @return
         */
        float Magnitude() const;
        float MagnitudeSquared() const;

        /**
         * Is a unit vector
         */
         Vector3 Normalized() const;

        /**
         * Project the vector on the parameter vector
         * @param in
         * @return
         */
        Vector3 ProjectOn(const Vector3& in) const;

        /**
         * Get the vector perpendicular from vector to the projection vector of given parameter
         * @param in
         * @return
         */
        Vector3 PerpendicularToProjection(const Vector3& in) const;
    };
}


#endif //MEOWENGINE_VECTOR3_HPP
