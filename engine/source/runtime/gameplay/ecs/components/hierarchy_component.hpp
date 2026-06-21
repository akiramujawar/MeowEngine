//
// Created by Akira Mujawar on 20/02/26.
//

#ifndef MEOWENGINE_HIERARCHY_COMPONENT_HPP
#define MEOWENGINE_HIERARCHY_COMPONENT_HPP

#include "component_base.hpp"
#include "EntityHandle.hpp"

namespace MeowEngine::component {
    class HierarchyComponent : public entity::ComponentBase {
    public:
        REFLECT_COMPONENT(HierarchyComponent)
        static void Reflect() {}

        HierarchyComponent();
        // HierarchyComponent(const entt::entity& pSelf,
        //                    const entt::entity& pParent,
        //                    const entt::entity& pFirstChild,
        //                    const entt::entity& pNext,
        //                    const entt::entity& pPrevious);
        ~HierarchyComponent() override = default;

    public:
        Runtime::EntityHandle Self;

        Runtime::EntityHandle Parent;
        Runtime::EntityHandle FirstChild;

        // next entity in the same hierarchy
        Runtime::EntityHandle NextChildOfParent;

        // previous entity in the same hierarchy
        Runtime::EntityHandle PreviousChildOfParent;
    };
}

#endif //MEOWENGINE_HIERARCHY_COMPONENT_HPP
