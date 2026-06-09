//
// Created by Akira Mujawar on 20/05/26.
//

#ifndef MEOWENGINE_RENDERPIPELINEMANAGER_HPP
#define MEOWENGINE_RENDERPIPELINEMANAGER_HPP

#include <typeindex>
#include <unordered_map>
#include <memory>
#include <type_traits>

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
        auto typeID = std::type_index(typeid(Type));

        // if exists return
        auto findIt = Pipelines.find(typeID);
        if (findIt != Pipelines.end()) {
            return static_cast<Type&>(*findIt->second);
        }

        // create and cache pipeline
        auto [createIt, isCreated] = Pipelines.emplace(typeID, std::make_unique<Type>());
        return static_cast<Type&>(*createIt->second);
    }
}

#endif //MEOWENGINE_RENDERPIPELINEMANAGER_HPP