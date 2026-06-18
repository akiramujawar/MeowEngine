//
// Created by Akira Mujawar on 15/03/26.
//

#ifndef MEOWENGINE_IDENTITYCOMPONENT_HPP
#define MEOWENGINE_IDENTITYCOMPONENT_HPP

#include <component_base.hpp>

namespace MeowEngine::Runtime {
    /**
     * Used as identifier. This can help with component references.
     */
    class IdentityComponent : public MeowEngine::entity::ComponentBase {
    public:
        REFLECT_COMPONENT(IdentityComponent)
        static void Reflect();

        IdentityComponent();

        [[nodiscard]] uint32_t GetGUID() const;
        void SetGUID(uint32_t guid);

    private:
        uint32_t GUID;
    };
}

#endif //MEOWENGINE_IDENTITYCOMPONENT_HPP