//
// Created by Akira Mujawar on 20/02/26.
//

#ifndef MEOWENGINE_HIERARCHY_COMPONENT_HPP
#define MEOWENGINE_HIERARCHY_COMPONENT_HPP

#include "IComponent.hpp"
#include "EntityHandle.hpp"

namespace MeowEngine::Runtime {
    // TODO: serialize this (update macro for properties which need to be hidden)
    class HierarchyComponent : public IComponent {
    public:
        REFLECT_COMPONENT(HierarchyComponent)
        static void Reflect();

        HierarchyComponent();
        ~HierarchyComponent() override = default;

    public:
        EntityHandle Self;

        EntityHandle Parent;

        // first and last entity inside
        EntityHandle FirstChild;
        // EntityHandle LastChild;

        // next & previous entity in the same hierarchy
        EntityHandle NextChildOfParent;
        EntityHandle PreviousChildOfParent;
    };
}

#endif //MEOWENGINE_HIERARCHY_COMPONENT_HPP
