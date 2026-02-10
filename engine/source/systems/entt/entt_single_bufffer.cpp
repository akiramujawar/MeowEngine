//
// Created by Akira Mujawar on 27/01/25.
//

#include "entt_single_buffer.hpp"

namespace MeowEngine {
    EnttSingleBuffer::EnttSingleBuffer() {}

    entt::registry &EnttSingleBuffer::GetCurrent() {
        return Current;
    }

    entt::entity EnttSingleBuffer::AddEntity() {
        return Current.create();
    }

    void MeowEngine::EnttSingleBuffer::RemoveEntity(entt::entity &inEntity) {
        GetCurrent().destroy(inEntity);
    }

    void MeowEngine::EnttSingleBuffer::RemoveEntity(const entt::entity &inEntity) {
        GetCurrent().destroy(inEntity);
    }

    void EnttSingleBuffer::ApplyPropertyChange() {

    }
} // MeowEngine