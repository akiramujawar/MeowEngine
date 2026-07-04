//
// Created by Akira Mujawar on 04/07/26.
//

#include "HierarchyManager.hpp"

#include "HierarchyComponent.hpp"
#include "World.hpp"

namespace MeowEngine::Runtime {

    void HierarchyManager::DetachParent(Asset::World& world, const EntityHandle& child) {
        auto& childHierarchy = world.GetComponent<HierarchyComponent>(child);

        // if has parent remove references first
        if (childHierarchy.Parent.GetIsValid()) {
            auto previousChild = childHierarchy.PreviousChildOfParent;
            auto nextChild = childHierarchy.NextChildOfParent;

            // reset if first chlid of parent is same as moved entity
            auto& previousParentHierarchy = world.GetComponent<HierarchyComponent>(childHierarchy.Parent);
            if (previousParentHierarchy.FirstChild.GetGUID() == child.GetGUID()) {
                // update first child if a child already exists inside the previousParent
                if (nextChild.GetIsValid()) {
                    previousParentHierarchy.FirstChild = nextChild;
                }
                // reset if no other childs exist
                else {
                    previousParentHierarchy.FirstChild = EntityHandle::Invalid();
                }
            }

            // reset child attachments
            if (previousChild.GetIsValid() && nextChild.GetIsValid()) {
                auto& previousChildHierarchy = world.GetComponent<HierarchyComponent>(previousChild);
                auto& nextChildHierarchy = world.GetComponent<HierarchyComponent>(nextChild);
                previousChildHierarchy.NextChildOfParent = nextChild;
                nextChildHierarchy.PreviousChildOfParent = previousChild;
            }
            else if (previousChild.GetIsValid()) {
                auto& previousChildHierarchy = world.GetComponent<HierarchyComponent>(previousChild);
                previousChildHierarchy.NextChildOfParent = EntityHandle::Invalid();
            }
            else if (nextChild.GetIsValid()) {
                auto& nextChildHierarchy = world.GetComponent<HierarchyComponent>(nextChild);
                nextChildHierarchy.PreviousChildOfParent = EntityHandle::Invalid();
            }
        }
    }

    void HierarchyManager::AttachParent(Asset::World& world, const EntityHandle& child , const EntityHandle& parent) {
        auto& childHierarchy = world.GetComponent<HierarchyComponent>(child);
        auto& parentEntity = world.GetComponent<HierarchyComponent>(parent);

        // if no child inside parent
        if (!parentEntity.FirstChild.GetIsValid()) {
            parentEntity.FirstChild = child;
            childHierarchy.Parent = parent;
        }
        // if child exists we set as last entity
        else {
            auto lastEntity = parentEntity.FirstChild;
            auto* lastHierarchy = &world.GetComponent<HierarchyComponent>(lastEntity);

            // retrieve the last entity
            while (lastHierarchy->NextChildOfParent.GetIsValid()) {
                lastEntity = lastHierarchy->NextChildOfParent;
                lastHierarchy = &world.GetComponent<HierarchyComponent>(lastEntity);
            }

            lastHierarchy->NextChildOfParent = child;
            childHierarchy.Parent = parent;
            childHierarchy.PreviousChildOfParent = lastEntity;
        }
    }

    void HierarchyManager::Reset(Asset::World& world, const EntityHandle& handle) {
        auto& hierarchy = world.GetComponent<HierarchyComponent>(handle);

        hierarchy.NextChildOfParent = EntityHandle::Invalid();
        hierarchy.PreviousChildOfParent = EntityHandle::Invalid();
        hierarchy.Parent = EntityHandle::Invalid();
    }

}
