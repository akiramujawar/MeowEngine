//
// Created by Akira Mujawar on 15/03/26.
//

#include <IdentityComponent.hpp>
#include <UUID.hpp>

namespace MeowEngine::Runtime {
    void IdentityComponent::Reflect() {}

    IdentityComponent::IdentityComponent() : GUID(Core::UUID::GenerateUUID()) {}

    uint32_t IdentityComponent::GetGUID() const {
        return GUID;
    }

    void IdentityComponent::SetGUID(const uint32_t guid) {
        GUID = guid;
    }
}
