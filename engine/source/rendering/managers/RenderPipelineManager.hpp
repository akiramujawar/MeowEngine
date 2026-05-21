//
// Created by Akira Mujawar on 20/05/26.
//

#ifndef MEOWENGINE_RENDERPIPELINEMANAGER_HPP
#define MEOWENGINE_RENDERPIPELINEMANAGER_HPP

#include <typeindex>
#include <unordered_map>

#include <IRenderPipeline.hpp>

namespace MeowEngine::Rendering {
    class RenderPipelineManager {
    public:
        RenderPipelineManager();
        ~RenderPipelineManager();

        template<typename Type>
        Type& GetPipeline();

    private:
        std::unordered_map<std::type_index, std::unique_ptr<IRenderPipeline>> Pipelines;
    };

    template <typename Type>
    Type& RenderPipelineManager::GetPipeline() {
        const auto typeID = std::type_index(typeid(Type));
        const auto iterator = Pipelines.find(typeID);

        return static_cast<Type&>(*iterator->second);
    }
}

#endif //MEOWENGINE_RENDERPIPELINEMANAGER_HPP