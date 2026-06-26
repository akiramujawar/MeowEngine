//
// Created by Akira Mujawar on 20/02/26.
//

#include "HierarchyComponent.hpp"

namespace MeowEngine::Runtime {
    void HierarchyComponent::Reflect() {
        REGISTER_PROPERTY(HierarchyComponent, Self, EntityHandle, false, false)
        REGISTER_PROPERTY(HierarchyComponent, Parent, EntityHandle, false, false)
        REGISTER_PROPERTY(HierarchyComponent, FirstChild, EntityHandle, false, false)
        REGISTER_PROPERTY(HierarchyComponent, NextChildOfParent, EntityHandle, false, false)
        REGISTER_PROPERTY(HierarchyComponent, PreviousChildOfParent, EntityHandle, false, false)
    }

    HierarchyComponent::HierarchyComponent()
        : Self()
        , Parent()
        , FirstChild()
        , NextChildOfParent()
        , PreviousChildOfParent()
    {}

}