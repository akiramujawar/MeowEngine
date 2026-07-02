//
// Created by Akira Mujawar on 01/07/26.
//

#include "TransformGizmoAsset.hpp"

namespace MeowEngine::Asset {
    TransformGizmoAsset::TransformGizmoAsset() {
        CreateHandle();
    }

    void TransformGizmoAsset::CreateHandle() {
        auto addVertex = [&](glm::vec3 pVertexPosition, int pAxis, int pHandleType) {
            Vertices.push_back(pVertexPosition.x);
            Vertices.push_back(pVertexPosition.y);
            Vertices.push_back(pVertexPosition.z);

            Vertices.push_back((float) pAxis);
            Vertices.push_back((float) pHandleType);

            return (uint32_t) (Vertices.size() / 5 - 1);
        };

        for (int axis = 0; axis < 3; axis++) {
            glm::vec3 direction(0.0f);
            direction[axis] = 1.0f;

            AddAxisLines(addVertex, axis);
            AddScaleCubes(addVertex, axis, direction);
            AddArrowHeads(addVertex, axis, direction);
            AddRotationRings(addVertex, axis);
        }
    }

    void TransformGizmoAsset::AddAxisLines(
        const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
        int pAxis
    ){
        float length = 1.0f;
        float radius = 0.01f;
        int lineSegments = 20;

        uint32_t baseIndex = Vertices.size() / 5;

        for (int i = 0; i < lineSegments; i++) {
            float t = (float)i / (float)lineSegments * glm::two_pi<float>();
            float nextT = (float) (i + 1) / (float)lineSegments * glm::two_pi<float>();

            glm::vec3 p0(0), p1(0), p2(0), p3(0);

            if (pAxis == 0) {
                p0 = {0, cos(t) * radius, sin(t) * radius};
                p1 = {length, cos(t) * radius, sin(t) * radius};
                p2 = {0, cos(nextT) * radius, sin(nextT) * radius};
                p3 = {length, cos(nextT) * radius, sin(nextT) * radius};
            }
            if (pAxis == 1) {
                p0 = {cos(t) * radius, 0, sin(t) * radius};
                p1 = {cos(t) * radius, length, sin(t) * radius};
                p2 = {cos(nextT) * radius, 0, sin(nextT) * radius};
                p3 = {cos(nextT) * radius, length, sin(nextT) * radius};
            }
            if (pAxis == 2) {
                p0 = {cos(t) * radius, sin(t) * radius, 0};
                p1 = {cos(t) * radius, sin(t) * radius, length};
                p2 = {cos(nextT) * radius, sin(nextT) * radius, 0};
                p3 = {cos(nextT) * radius, sin(nextT) * radius, length};
            }

            uint32_t i0 = pAddVertex(p0, pAxis, 0);
            uint32_t i1 = pAddVertex(p1, pAxis, 0);
            uint32_t i2 = pAddVertex(p2, pAxis, 0);
            uint32_t i3 = pAddVertex(p3, pAxis, 0);

            // two triangles per segment
            Indices.push_back(i0);
            Indices.push_back(i2);
            Indices.push_back(i1);

            Indices.push_back(i1);
            Indices.push_back(i2);
            Indices.push_back(i3);
        }
    }

    void TransformGizmoAsset::AddScaleCubes(
        const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
        int pAxis,
        glm::vec3 pDirection
    ){
        float cubeOffset = 0.5f;
        glm::vec3 cubeCenter = pDirection * cubeOffset;
        float s = 0.05f;

        glm::vec3 offsets[8] = {
                {-s, -s, -s},
                {s,  -s, -s},
                {s,  s,  -s},
                {-s, s,  -s},
                {-s, -s, s},
                {s,  -s, s},
                {s,  s,  s},
                {-s, s,  s}
        };

        uint32_t base = Vertices.size() / 5;

        for (int i = 0; i < 8; i++) {
            pAddVertex(cubeCenter + offsets[i], pAxis, 2);
        }

        uint32_t cubeInd[36] = {
                0, 1, 2, 2, 3, 0,
                4, 5, 6, 6, 7, 4,
                0, 4, 7, 7, 3, 0,
                1, 5, 6, 6, 2, 1,
                3, 2, 6, 6, 7, 3,
                0, 1, 5, 5, 4, 0
        };

        for (int i = 0; i < 36; i++) {
            Indices.push_back(base + cubeInd[i]);
        }
    }

    void TransformGizmoAsset::AddArrowHeads(
        const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
        int pAxis,
        glm::vec3 pDirection
    ){
        float arrowOffset = 1.0f;
        float arrowLength = 0.17f;
        float arrowRadius = 0.075f;
        int segments = 16;

        uint32_t arrowBaseIndex = Vertices.size() / 5;

        glm::vec3 tip = pDirection * (arrowOffset + arrowLength);

        // arrow tip
        uint32_t tipIndex = pAddVertex(tip, pAxis, 1);

        // arrow base circle
        for (int i = 0; i < segments; i++) {
            float t = (float) i / (float)segments * glm::two_pi<float>();

            glm::vec3 circle(0);

            if (pAxis == 0) {
                circle = {0, cos(t) * arrowRadius, sin(t) * arrowRadius};
            }

            if (pAxis == 1) {
                circle = {cos(t) * arrowRadius, 0, sin(t) * arrowRadius};
            }

            if (pAxis == 2) {
                circle = {cos(t) * arrowRadius, sin(t) * arrowRadius, 0};
            }

            glm::vec3 basePos = pDirection * arrowOffset + circle;
            pAddVertex(basePos, pAxis, 1);
        }

        // triangles for arrow
        uint32_t baseCircleStart = arrowBaseIndex + 1; // first base vertex
        for (int i = 0; i < segments; i++) {
            uint32_t curr = baseCircleStart + i;
            uint32_t next = baseCircleStart + ((i + 1) % segments);

            // CCW winding
            Indices.push_back(curr);
            Indices.push_back(next);
            Indices.push_back(tipIndex);
        }
    }


    void TransformGizmoAsset::AddRotationRings(
        const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
        int pAxis
    ){
        float ringRadius = 0.75f;
        float thickness = 0.02f;

        float ringSegments = 64;
        int tubeSegments = 12;

        for (int i = 0; i < ringSegments; i++) {
            float theta = (float) i / ringSegments * glm::two_pi<float>();
            float nextTheta = (float) (i + 1) / ringSegments * glm::two_pi<float>();

            for (int j = 0; j < tubeSegments; j++) {
                float phi = (float) j / (float)tubeSegments * glm::two_pi<float>();
                float nextPhi = (float) (j + 1) / (float)tubeSegments * glm::two_pi<float>();

                auto ringPoint = [&](float theta, float phi) {
                    float R = ringRadius;
                    float r = thickness;

                    // canonical torus around Z axis
                    float x = (R + r * cos(phi)) * cos(theta);
                    float y = (R + r * cos(phi)) * sin(theta);
                    float z = r * sin(phi);

                    glm::vec3 p(x, y, z);

                    // rotate into correct axis
                    if (pAxis == 0) {
                        // rotate 90° around Y
                        p = glm::vec3(p.z, p.y, -p.x);
                    } else if (pAxis == 1) {
                        // rotate -90° around X
                        p = glm::vec3(p.x, p.z, -p.y);
                    }
                    // no rotation needed for Z

                    return p;
                };

                glm::vec3 p0 = ringPoint(theta, phi);
                glm::vec3 p1 = ringPoint(nextTheta, phi);
                glm::vec3 p2 = ringPoint(theta, nextPhi);
                glm::vec3 p3 = ringPoint(nextTheta, nextPhi);

                uint32_t i0 = pAddVertex(p0, pAxis, 3);
                uint32_t i1 = pAddVertex(p1, pAxis, 3);
                uint32_t i2 = pAddVertex(p2, pAxis, 3);
                uint32_t i3 = pAddVertex(p3, pAxis, 3);

                // two triangles per quad
                Indices.push_back(i0);
                Indices.push_back(i2);
                Indices.push_back(i1);

                Indices.push_back(i1);
                Indices.push_back(i2);
                Indices.push_back(i3);
            }
        }
    }
}
