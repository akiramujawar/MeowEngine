//
// Created by Akira Mujawar on 20/02/26.
//

#ifndef MEOWENGINE_HIERARCHY_COMPONENT_HPP
#define MEOWENGINE_HIERARCHY_COMPONENT_HPP

#include "component_base.hpp"

namespace MeowEngine::component {
    class HierarchyComponent : public entity::ComponentBase {
    public:
        REFLECT_COMPONENT(HierarchyComponent)
        static void Reflect() {}

        HierarchyComponent(const entt::entity& pSelf,
                           const entt::entity& pParent,
                           const entt::entity& pFirstChild,
                           const entt::entity& pNext,
                           const entt::entity& pPrevious);
        ~HierarchyComponent();

    public:
        entt::entity Self;

        entt::entity Parent;
        entt::entity FirstChild;

        // next entity in the same hierarchy
        entt::entity Next;

        // previous entity in the same hierarchy
        entt::entity Previous;
    };
}

#endif //MEOWENGINE_HIERARCHY_COMPONENT_HPP
