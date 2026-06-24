//
// Created by Akira Mujawar on 03/07/24.
//

#ifndef MEOWENGINE_TRANSFORM_COMPONENT_BASE_HPP
#define MEOWENGINE_TRANSFORM_COMPONENT_BASE_HPP

#include "ComponentBase.hpp"
#include "GLM_API.hpp"

namespace MeowEngine::Runtime {
class TransformComponentBase : public MeowEngine::Runtime::ComponentBase {

    public:
        TransformComponentBase();
        virtual ~TransformComponentBase() = default;

        virtual void Update(const float& deltaTime) = 0;
    };
}


#endif //MEOWENGINE_TRANSFORM_COMPONENT_BASE_HPP
