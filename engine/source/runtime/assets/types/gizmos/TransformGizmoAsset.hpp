//
// Created by Akira Mujawar on 01/07/26.
//

#ifndef MEOWENGINE_TRANSFORMGIZMOASSET_HPP
#define MEOWENGINE_TRANSFORMGIZMOASSET_HPP

#include "GLM_API.hpp"
// #include "IAsset.hpp"
#include "GizmoAsset.hpp"

namespace MeowEngine::Asset {
    class TransformGizmoAsset : public GizmoAsset {
    public:
        TransformGizmoAsset();
        ~TransformGizmoAsset() override = default;

    private:
        void CreateHandle();

        void AddAxisLines(const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
                          int pAxis);

        void AddScaleCubes(const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
                           int pAxis,
                           glm::vec3 pDirection);

        void AddArrowHeads(const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
                           int pAxis,
                           glm::vec3 pDirection);

        void AddRotationRings(const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
                              int pAxis);

    // private:
    //     std::vector<float> Vertices;
    //     std::vector<uint32_t> Indices;
    };
}


#endif //MEOWENGINE_TRANSFORMGIZMOASSET_HPP