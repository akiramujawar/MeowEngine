//
// Created by Akira Mujawar on 15/03/26.
//

#include <IdentityComponent.hpp>


namespace MeowEngine::Runtime {
    void IdentityComponent::Reflect() {}

    IdentityComponent::IdentityComponent() : GUID(0) {}

    uint32_t IdentityComponent::GetGUID() const {
        return GUID;
    }

    void IdentityComponent::SetGUID(const uint32_t guid) {
        GUID = guid;
    }
}
