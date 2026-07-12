//
// Created by Akira Mujawar on 26/01/26.
//

#ifndef MEOWENGINE_MATRIX4X4_HPP
#define MEOWENGINE_MATRIX4X4_HPP

#include "GLM_API.hpp"

#include "vector3.hpp"
#include "Quaternion.hpp"

namespace MeowEngine::Core::Math {
    /**
     * TODO: implement const methods
     * @tparam T int, float, double...
     * @tparam Rows
     * @tparam Columns
     */
    template<typename T, int Rows, int Columns>
    struct Matrix {
        static void Reflect();

    public:
        // glm -> col, major
        // opengl -> col, major
        T Elements[Rows * Columns];

        std::string ToString() {
            std::string value = "[";
            for (int i = 0 ; i < Rows ; i++) {
                for (int j = 0 ; j < Columns ; j++) {
                    value += T(i, j);
                }
                value += "\n";
            }

            value += "]";

            return value;
        }

        /**
         * Column Major
         * @param col
         * @return
         */
        constexpr T* operator[](int col) {
            return &Elements[col * Rows];
        }

        constexpr const T* operator[](int col) const {
            return &Elements[col * Rows];
        }

        /**
         * Row Major
         * @param row
         * @param col
         * @return
         */
        constexpr T& operator()(int row, int col) {
            return Elements[col * Rows + row];
        }

        constexpr const T& operator()(int row, int col) const{
            return Elements[col * Rows + row];
        }

        /**
         * Only for square matrices like 2x2, 3x3, 4x4 etc...
         * NOTE: also please reimplement this :)
         * @param value
         * @return
         */
        constexpr Matrix operator*(const Matrix& value) {
            Matrix matrix = Zero();

            for (int row = 0; row < Rows; ++row) {
                for (int col = 0; col < Columns; ++col) {
                    for (int k = 0; k < Columns; ++k) {
                        matrix(row, col) +=(*this)(row, k) * value(k, col);
                    }
                }
            }

            return matrix;
        }

        /**
         * Only for square matrices like 2x2, 3x3, 4x4 etc...
         * NOTE: also please reimplement this :)
         * @param value
         * @return
         */
        constexpr Matrix operator*(const Matrix& value) const {
            Matrix matrix = Zero();

            for (int row = 0; row < Rows; ++row) {
                for (int col = 0; col < Columns; ++col) {
                    for (int k = 0; k < Columns; ++k) {
                        matrix(row, col) +=(*this)(row, k) * value(k, col);
                    }
                }
            }

            return matrix;
        }

        /**
         * Continuous memoery (col major)
         * @return
         */
        constexpr T* Data() {
            return &Elements;
        }

        static constexpr Matrix Identity() {
            Matrix matrix = Zero();
            int small = std::min(Rows, Columns);
            for (int i = 0 ; i < small ; i++) {
                matrix[i][i] = T(1);
            }

            return matrix;
        }

        static constexpr Matrix Zero() {
            return {};
        }

        // void Product();
        // void Inverse();
        // void Determinant();
        // void Orthogonal();
        // void Transpose();

        // translation , scaling & rotating
        static Matrix Translate(const Vector3& translation) {
            Matrix matrix = Identity();

            matrix[3][0] = translation.X;
            matrix[3][1] = translation.Y;
            matrix[3][2] = translation.Z;

            return matrix;
        }

        static Matrix Scale(const Vector3& scale) {
            Matrix matrix = Identity();

            matrix[0][0] = scale.X;
            matrix[1][1] = scale.Y;
            matrix[2][2] = scale.Z;

            return matrix;
        }


        static Matrix Rotation3x3(const Quaternion& quat) {
            float xSquare = quat.X * quat.X;
            float ySquare = quat.Y * quat.Y;
            float zSquare = quat.Z * quat.Z;

            float XY = quat.X * quat.Y;
            float XZ = quat.X * quat.Z;
            float YZ = quat.Y * quat.Z;

            float WX = quat.W * quat.X;
            float WY = quat.W * quat.Y;
            float WZ = quat.W * quat.Z;

            Matrix matrix {};

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

        static Matrix Rotation4x4(const Quaternion& quat) {
            float xSquare = quat.X * quat.X;
            float ySquare = quat.Y * quat.Y;
            float zSquare = quat.Z * quat.Z;

            float XY = quat.X * quat.Y;
            float XZ = quat.X * quat.Z;
            float YZ = quat.Y * quat.Z;

            float WX = quat.W * quat.X;
            float WY = quat.W * quat.Y;
            float WZ = quat.W * quat.Z;

            Matrix matrix {};

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


        // -- GLM ------------------------
        static Matrix Matrix4X4FromGlm(const glm::mat4 value) {
            Matrix matrix {};

            matrix[0][0] = value[0][0];
            matrix[0][1] = value[0][1];
            matrix[0][2] = value[0][2];
            matrix[0][3] = value[0][3];

            matrix[1][0] = value[1][0];
            matrix[1][1] = value[1][1];
            matrix[1][2] = value[1][2];
            matrix[1][3] = value[1][3];

            matrix[2][0] = value[2][0];
            matrix[2][1] = value[2][1];
            matrix[2][2] = value[2][2];
            matrix[2][3] = value[2][3];

            matrix[3][0] = value[3][0];
            matrix[3][1] = value[3][1];
            matrix[3][2] = value[3][2];
            matrix[3][3] = value[3][3];

            return matrix;
        }

        static glm::mat4 GlmFromMatrix4x4(Matrix pValue) {
            glm::mat4 rotation4Matrix {};

            rotation4Matrix[0][0] = pValue[0][0];
            rotation4Matrix[0][1] = pValue[0][1];
            rotation4Matrix[0][2] = pValue[0][2];
            rotation4Matrix[0][3] = pValue[0][3];

            rotation4Matrix[1][0] = pValue[1][0];
            rotation4Matrix[1][1] = pValue[1][1];
            rotation4Matrix[1][2] = pValue[1][2];
            rotation4Matrix[1][3] = pValue[1][3];

            rotation4Matrix[2][0] = pValue[2][0];
            rotation4Matrix[2][1] = pValue[2][1];
            rotation4Matrix[2][2] = pValue[2][2];
            rotation4Matrix[2][3] = pValue[2][3];

            rotation4Matrix[3][0] = pValue[3][0];
            rotation4Matrix[3][1] = pValue[3][1];
            rotation4Matrix[3][2] = pValue[3][2];
            rotation4Matrix[3][3] = pValue[3][3];

            return rotation4Matrix;
        }


    };

    using Matrix3x3 = Matrix<float, 3, 3>;
    using Matrix4x4 = Matrix<float, 4, 4>;

}


#endif //MEOWENGINE_MATRIX4X4_HPP
