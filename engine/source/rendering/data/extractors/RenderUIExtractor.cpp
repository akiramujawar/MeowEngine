//
// Created by Akira Mujawar on 09/06/26.
//

#include <RenderUIExtractor.hpp>

// core
#include <Public/Threading/Include.hpp>

// runtime
#include <GameplaySystem.hpp>
#include <World.hpp>

// editor
#include <Selector.hpp>

// components
#include <IdentityComponent.hpp>
#include <info_component.hpp>
#include <hierarchy_component.hpp>

namespace MeowEngine::Rendering {

    RenderUIExtractor::RenderUIExtractor() {}

    RenderUIExtractor::~RenderUIExtractor() {}

    void RenderUIExtractor::Init(const RenderUIExtractorInitData& data) {
        Gameplay = data.Gameplay;
        Selector = data.Selector;
    }

    void RenderUIExtractor::Schedule(Threading::Scheduler& scheduler) {
        scheduler.AddTask(
            [this]() {
                Clear();
                Extract();
            }
        );

        // swap buffers (internally only swaps if buffers are not locked)
        scheduler.AddTask(
            [this]() {
                RenderUIData.Swap();
            }
        );
    }

    void RenderUIExtractor::Clear() {
        auto& frame = RenderUIData.GetCurrent();
        frame.RootEntities.clear();
        frame.EntityHierarchyMap.clear();
        frame.SelectedEntities.clear();
    }

    void RenderUIExtractor::Extract() {
        PT_PROFILE_SCOPE;

        auto& world = Gameplay->GetWorld();
        auto& ecs = world.GetRegistry();
        auto& frame = RenderUIData.GetCurrent();

        // extract entities for tree panel
        auto view = ecs.view<Runtime::IdentityComponent, entity::InfoComponent, component::HierarchyComponent>();
        std::function<void(entt::entity)> extractEntityHierarchy;

        // dynamic method for getting the child entities
        extractEntityHierarchy = [&ecs, &frame, &view, &extractEntityHierarchy](entt::entity entity) {
            auto&& [identity, info, hierarchy] = view.get(entity);

            std::vector<uint32_t> childs;
            entt::entity child = hierarchy.FirstChild;

            // recursively expand and get all child uuid's for given entity parent
            while (child != entt::null) {
                extractEntityHierarchy(child);

                // track child uuid (for render data)
                auto childIdentity = ecs.get<Runtime::IdentityComponent>(child);
                childs.push_back(childIdentity.GetGUID());

                // select to next child to iterate
                child = ecs.get<component::HierarchyComponent>(child).NextChildOfParent;
            }

            // track the entity data (for render data)
            frame.EntityHierarchyMap.emplace(identity.GetGUID(), RenderEntityHierarchy {
                identity.GetGUID(), info.GetName(), std::move(childs)
            });
        };

        // select only root entities and expand on them
        for (auto& entity : view) {
            auto&& hierarchy = ecs.get<component::HierarchyComponent>(entity);

            // only select root entities (we expand childs inside)
            if (!ecs.valid(hierarchy.Parent)) {
                // track entity guid (only root)
                auto&& identity = ecs.get<Runtime::IdentityComponent>(entity);
                frame.RootEntities.push_back(identity.GetGUID());

                extractEntityHierarchy(entity);
            }
        }

        // track selected entities
        for (const auto entity : Selector->SelectedEntities) {
             auto identity = ecs.get<Runtime::IdentityComponent>(entity);
            frame.SelectedEntities.emplace(identity.GetGUID());
        }
    }

}
