//
// Created by Akira Mujawar on 11/03/26.
//

#include <WorldSerializer.hpp>

// #include <Public/IO.hpp>
#include "MeowService.hpp"
#include "AssetSerializer.hpp"
#include "ComponentSerializer.hpp"

// #include "hierarchy_component.hpp"
#include "info_component.hpp"
#include "entt.hpp"
#include <Project.hpp>

#include "IdentityComponent.hpp"


// #define TEST(Registry, Type, Entity, Args) \
//     Registry.emplace<Type>(Entity, Args);
//
// #define TEST2(Registry, Type, Entity, Args) TEST(Registry, Type, Entity, Args)

// template<typename ComponentType>
// void* AddComponent(entt::registry& registry, entt::entity &inEntity) {
//     auto* test = new ComponentType();
//
//     registry.emplace<MeowEngine::entity::InfoComponent>(inEntity, std::move(test));
//
//     return static_cast<void*>(test);
// }
//
// std::map<std::string, void*(*)(entt::registry& registry, entt::entity &inEntity)> AddComponentMap;

template<typename ComponentType>
void* AddComponent(entt::registry& registry, entt::entity &inEntity) {
    auto& test = registry.emplace<ComponentType>(inEntity);

    return &test;
}

std::map<std::string, void*(*)(entt::registry& registry, entt::entity& inEntity)> AddComponentMap;

void Test123() {
    AddComponentMap["InfoComponent"] = &AddComponent<MeowEngine::entity::InfoComponent>;

    AddComponentMap.try_emplace(
        "InfoComponent",
        &AddComponent<MeowEngine::entity::InfoComponent>
    );
    // AddComponentMap["HierarchyComponent"] = &AddComponent<MeowEngine::component::HierarchyComponent>;

}

std::map<int32_t, entt::entity> entityGUID_Map;

namespace MeowEngine::Asset {
    bool WorldSerializer::Serialize(const FileSystem::Path path, Runtime::World& world) {
        MeowEngine::Log("WorldSerializer", "Serialize");

        // template world data for testing
        auto testWorld = Runtime::World();
        auto& registry = testWorld.GetBuffer().GetCurrent();

        entt::entity testEntity = registry.create();
        auto identityComponent = registry.emplace<Runtime::IdentityComponent>(testEntity);
        auto infoComponent = registry.emplace<entity::InfoComponent>(testEntity);

        identityComponent.SetGUID(5556);
        infoComponent.SetName(String("testEntity"));

        // read existing header
        auto readSerializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);
        AssetHeader header;
        AssetSerializer::ReadHeader(readSerializer, header);
        AssetSerializer::CloseSerializer(readSerializer);

        auto tempPath = path;
        tempPath.ReplaceExtension("meowtemp");

        // -------- serialization ahead
        auto writeSerializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::WRITE);
        AssetSerializer::WriteHeader(writeSerializer, header);

        // save entity count
        size_t entityCount = registry.storage<entt::entity>().size();
        writeSerializer.WriteSize(entityCount);

        // save all guids
        registry.view<Runtime::IdentityComponent>().each([&writeSerializer](const Runtime::IdentityComponent& identity) {
            writeSerializer.WriteUInt32(identity.GetGUID());
        });

        // guid, component count, component name & its serialized data (using reflection system)
        registry.view<entt::entity, Runtime::IdentityComponent>().each([&registry, &writeSerializer](const entt::entity entity, const Runtime::IdentityComponent& identity) {
            // cache and save entity guid
            const auto guid = identity.GetGUID();
            writeSerializer.WriteUInt32(guid);

            // count components (not the best way)
            uint16_t componentCount = 0;

            // use && for reference (as it is unknown type & we want reference not a copy
            for (auto&& [id, component]: registry.storage()) {
                if (component.contains(entity)) {
                    componentCount++;
                }
            }

            // save component counts
            writeSerializer.WriteUInt16(componentCount);

            // serialize & save component data
            // component = vector storage of that component for every entity using it
            for (auto&& [id, component]: registry.storage()) {
                if (component.contains(entity)) {
                    const entt::id_type type = id;
                    const std::string componentName = MeowEngine::GetReflection().GetComponentName(type);
                    writeSerializer.WriteString(componentName);

                    // properties
                    void* componentObject = component.value(entity);
                    Asset::ComponentSerializer::Serialize(writeSerializer, componentObject, componentName);
                }
            }
        });

        AssetSerializer::CloseSerializer(writeSerializer);

        if (!FileSystem::FileSystem::Replace(path, tempPath)) {
            FileSystem::FileSystem::Remove(tempPath);

            return false;
        }

        return true;
    }

    bool WorldSerializer::Deserialize(const FileSystem::Path path, Runtime::World& world) {
        // auto testWorld = World();
        auto& registry = world.GetBuffer().GetCurrent();

        // --------------- serialization ahead
        auto serializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);

        AssetHeader header;
        const bool isValidAsset = AssetSerializer::ReadHeader(serializer, header);

        if (!isValidAsset) {
            return false;
        }

        size_t entityCount;
        entityCount = serializer.ReadSize();
        // stream.Read(&entityCount, sizeof(size_t));
        MeowEngine::Log("Deserialize", (int)entityCount);

        for (auto i = 0; i < entityCount; i++) {
            auto entity = world.GetBuffer().AddEntity();
            auto instance = AddComponentMap["InfoComponent"](registry, entity);

            ComponentSerializer::Deserialize(serializer, instance, "InfoComponent");

            // world.GetBuffer().AddComponent<Runtime::IdentityComponent>(entity);
            // add component - multithread
            // set data for a component - multithread
            // through component->method->(dyanmic args)

            // auto entity = registry.create();
            // uint32_t guid;
            // stream.Read(&guid, sizeof(uint32_t));

            // AddComponentMap["IdentityComponent"](registry, entity);

            // first read counts of entity
            // read the guid's and assign for that count
            // read guid
            // read the components
            // find the entity and process to attach components & it's assign data
        }

        AssetSerializer::CloseSerializer(serializer);

        return true;
    }
}
