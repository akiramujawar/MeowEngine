//
// Created by Akira Mujawar on 15/03/26.
//

#ifndef MEOWENGINE_IDENTITYCOMPONENT_HPP
#define MEOWENGINE_IDENTITYCOMPONENT_HPP

#include <IComponent.hpp>

#include "EntityHandle.hpp"

namespace MeowEngine::Runtime {
    /**
     * Used as identifier. This can help with component references.
     */
    class IdentityComponent : public IComponent {
    public:
        REFLECT_COMPONENT(IdentityComponent)
        static void Reflect();

        IdentityComponent();

        [[nodiscard]] uint64_t GetGUIDInt() const { return Handle.GetGUIDInt(); }
        [[nodiscard]] EntityID GetGUID() const { return Handle.GetGUID(); };
        [[nodiscard]] Entity GetEntity() const { return Handle.GetEntity(); };
        [[nodiscard]] EntityHandle GetEntityHandle() const { return Handle; };

        void Set(EntityID guid, Entity entity);
        void Set(EntityHandle entity);

    private:
        EntityHandle Handle;
    };
}

#endif //MEOWENGINE_IDENTITYCOMPONENT_HPP