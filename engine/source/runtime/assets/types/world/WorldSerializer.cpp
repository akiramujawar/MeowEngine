//
// Created by Akira Mujawar on 11/03/26.
//

#include <WorldSerializer.hpp>

#include "Public/IO/Include.hpp"
#include "AssetSerializer.hpp"
#include "ComponentSerializer.hpp"

#include "info_component.hpp"
#include "reflection_test_component.hpp"
#include "IdentityComponent.hpp"
#include "ComponentID.hpp"


namespace MeowEngine::Asset {
    bool WorldSerializer::Serialize(const FileSystem::Path& path, World& world) {
        MeowEngine::Log("WorldSerializer::Serialize", "");

        // // template world data for testing
        // auto testWorld = Asset::World();
        // auto& registry = testWorld.GetRegistry();
        //
        // Runtime::EntityHandle testEntity = testWorld.AddEntity();
        // auto& info = testWorld.GetComponent<entity::InfoComponent>(testEntity);
        // auto& reflection = testWorld.AddComponent<entity::ReflectionTestComponent>(testEntity);
        // reflection.Init();
        // info.SetName(String("testEntity"));

        auto& registry = world.GetRegistry();

        // read existing header
        auto readSerializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);
        AssetHeader header;
        AssetSerializer::ReadHeader(readSerializer, header);
        AssetSerializer::CloseSerializer(readSerializer);

        auto tempPath = path;
        tempPath.ReplaceExtension("meowtemp");

        // -------- serialization ahead
        auto writeSerializer = AssetSerializer::OpenSerializer(tempPath, FileSystem::FileMode::WRITE);
        AssetSerializer::WriteHeader(writeSerializer, header);

        // save entity count
        size_t entityCount = registry.storage<Runtime::Entity>().size() - 1;
        writeSerializer.WriteSize(entityCount);

        // save all guids
        registry.view<Runtime::IdentityComponent>().each([&writeSerializer](const Runtime::IdentityComponent& identity) {
            writeSerializer.WriteUInt64(identity.GetGUIDInt());
        });

        // guid, component count, component name & its serialized data (using reflection system)
        registry.view<Runtime::Entity, Runtime::IdentityComponent>().each([&registry, &writeSerializer](const Runtime::Entity entity, const Runtime::IdentityComponent& identity) {
            // cache and save entity guid
            const auto guid = identity.GetGUIDInt();
            writeSerializer.WriteUInt64(guid);

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
            for (auto&& [id, component]: registry.storage()) {
                if (component.contains(entity)) {
                    const Runtime::ComponentID type = id;
                    const std::string componentName = MeowEngine::GetReflection().GetComponentName(type);

                    writeSerializer.WriteString(componentName);

                    // properties
                    void* componentObject = component.value(entity);
                    ComponentSerializer::Serialize(writeSerializer, componentObject, componentName);
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

    bool WorldSerializer::Deserialize(const FileSystem::Path& path, World& world) {
        MeowEngine::Log("WorldSerializer::Deserialize", path.GetRawString());

        // auto testWorld = World();
        auto& registry = world.GetRegistry();

        // --------------- serialization ahead
        auto serializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);

        AssetHeader header;
        const bool isValidAsset = AssetSerializer::ReadHeader(serializer, header);

        if (!isValidAsset) {
            return false;
        }

        // get all the guid's and entities & collect EntityHandles
        std::unordered_map<Runtime::EntityID, Runtime::EntityHandle> handles;
        std::vector<Runtime::EntityID> guids;
        size_t entityCount = serializer.ReadSize();

        for (auto i = 0; i < entityCount; i++) {
            const auto guidInt = serializer.ReadUInt64();
            const auto guid = Runtime::EntityID {guidInt};
            guids.push_back(guid);
        }

        // reverse the order of creation to match the original order
        std::reverse(guids.begin(), guids.end());
        for (auto guid : guids) {
            auto handle = world.AddEntity(guid);

            handles.try_emplace(guid, handle);
        }

        // for each serialized item
        // get handle -> get entity -> serialize
        for (auto i = 0 ; i < entityCount; i++) {
            const auto guidInt = serializer.ReadUInt64();
            const auto guid = Runtime::EntityID {guidInt};
            const auto componentCount = serializer.ReadUInt16();

            // add components
            for (auto j = 0; j < componentCount; j++) {
                std::string componentName = serializer.ReadString();
                auto addComponentMethod = GetReflection().GetAddComponentCallback(componentName);
                auto handle = handles.find(guid);

                // set properties
                void* componentObject = addComponentMethod(world, handle->second);
                ComponentSerializer::Deserialize(serializer, componentObject, componentName);
            }
        }

        AssetSerializer::CloseSerializer(serializer);

        return true;
    }
}
