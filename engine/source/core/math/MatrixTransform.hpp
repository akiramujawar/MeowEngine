//
// Created by Akira Mujawar on 26/06/26.
//

#ifndef MEOWENGINE_MATRIXTRANSFORM_HPP
#define MEOWENGINE_MATRIXTRANSFORM_HPP

#include "GLM_API.hpp"
#include "vector3.hpp"
#include "matrix4x4.hpp"

namespace MeowEngine::Core::Math {
    struct MatrixTransform {
    public:
        static Matrix4x4 LookAtRH(Vector3 position, Vector3 target, Vector3 up) {
            const auto positionGLM = Vector3::GlmFromVector3(position);
            const auto targetGLM = Vector3::GlmFromVector3(target);
            const auto upGLM = Vector3::GlmFromVector3(up);

            return Matrix4x4::Matrix4X4FromGlm(glm::lookAtRH(positionGLM, targetGLM, upGLM));
        }
    };
}


#endif //MEOWENGINE_MATRIXTRANSFORM_HPP