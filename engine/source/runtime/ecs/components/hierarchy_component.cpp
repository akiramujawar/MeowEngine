//
// Created by Akira Mujawar on 20/02/26.
//

#include "hierarchy_component.hpp"

namespace MeowEngine::component {
    HierarchyComponent::HierarchyComponent(const entt::entity& pSelf,
                                           const entt::entity& pParent,
                                           const entt::entity& pFirstChild,
                                           const entt::entity& pNext,
                                           const entt::entity& pPrevious)
        : Self(pSelf)
        , Parent(pParent)
        , FirstChild(pFirstChild)
        , Next(pNext)
        , Previous(pPrevious) {

    }

    HierarchyComponent::~HierarchyComponent() {

    }
}