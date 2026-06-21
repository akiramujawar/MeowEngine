//
// Created by Akira Mujawar on 27/01/25.
//

#ifndef MEOWENGINE_ENTT_SINGLE_BUFFER_HPP
#define MEOWENGINE_ENTT_SINGLE_BUFFER_HPP

#include "entt_buffer_base.hpp"

namespace MeowEngine {

    struct EnttSingleBuffer : public MeowEngine::EnttBufferBase {
        EnttSingleBuffer();

        entt::registry& GetCurrent() override;
        entt::entity AddEntity() override;
        void RemoveEntity(entt::entity& inEntity);
        void RemoveEntity(const entt::entity& inEntity);

        /**
         * Registers components to keep the storage in order,
         * that way when we swap buffers we get the fixed order of component
         * @tparam ComponentType
         */
        template<typename ComponentType>
        void RegisterComponent();

        template<typename ComponentType, typename... Args>
        void AddComponent(entt::entity& inEntity, Args &&...inArgs);

        template<typename ComponentType, typename... Args>
        void AddComponent(const entt::entity& inEntity, Args &&...inArgs);

        template<typename ComponentType>
        void RemoveComponent(entt::entity& inEntity);

        template<typename ComponentType>
        void RemoveComponent(const entt::entity& inEntity);

        void ApplyPropertyChange() override;

    protected:
        entt::registry Current;
    };

    template<typename ComponentType>
    void MeowEngine::EnttSingleBuffer::RegisterComponent() {
        GetCurrent().storage<ComponentType>();
    }

    template<typename ComponentType, typename... Args>
    void MeowEngine::EnttSingleBuffer::AddComponent(entt::entity &inEntity, Args &&... inArgs) {
        Current.emplace<ComponentType>(inEntity, std::forward<Args>(inArgs)...);
    }

    template<typename ComponentType, typename... Args>
    void MeowEngine::EnttSingleBuffer::AddComponent(const entt::entity &inEntity, Args &&... inArgs) {
        Current.emplace<ComponentType>(inEntity, std::forward<Args>(inArgs)...);
    }

    template<typename ComponentType>
    void MeowEngine::EnttSingleBuffer::RemoveComponent(entt::entity &inEntity) {}

    template<typename ComponentType>
    void MeowEngine::EnttSingleBuffer::RemoveComponent(const entt::entity &inEntity) {}

} // MeowEngine

#endif //MEOWENGINE_ENTT_SINGLE_BUFFER_HPP
