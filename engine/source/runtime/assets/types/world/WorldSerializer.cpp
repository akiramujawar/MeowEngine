//
// Created by Akira Mujawar on 11/03/26.
//

#include <WorldSerializer.hpp>

#include <Public/IO.hpp>
#include <MeowService.hpp>

// #include "hierarchy_component.hpp"
#include "info_component.hpp"
#include "entt.hpp"
#include <Project.hpp>

#include "IdentityComponent.hpp"


// #define TEST(Registry, Type, Entity, Args) \
//     Registry.emplace<Type>(Entity, Args);
//
// #define TEST2(Registry, Type, Entity, Args) TEST(Registry, Type, Entity, Args)

template<typename ComponentType>
void* AddComponent(entt::registry& registry, entt::entity &inEntity) {
    auto* test = new ComponentType();

    registry.emplace<MeowEngine::entity::InfoComponent>(inEntity, std::move(test));

    return static_cast<void*>(test);
}

std::map<std::string, void*(*)(entt::registry& registry, entt::entity &inEntity)> AddComponentMap;

void Test123() {
    // AddComponentMap["InfoComponent"] = &AddComponent<MeowEngine::entity::InfoComponent>;
    // AddComponentMap["HierarchyComponent"] = &AddComponent<MeowEngine::component::HierarchyComponent>;

}

std::map<int32_t, entt::entity> entityGUID_Map;

namespace {
    void SerializeClass(MeowEngine::Serialization::Serializer& serializer, void* instance, std::string className) {
        // properties
        auto properties = MeowEngine::GetReflection().GetProperties(className);
        for (auto& property : properties) {
            switch (property.Type) {
                case MeowEngine::PRIMITIVE: {
                    auto data = property.Get(instance);
                    if (property.TypeId == typeid(int)) {
                        int value = *static_cast<int*>(data);
                        std::string name = property.Name;

                        serializer.WriteString(name);
                        serializer.WriteInt(value);
                    }
                    else if (property.TypeId == typeid(float)) {
                        float value = *static_cast<float*>(data);
                        std::string name = property.Name;

                        serializer.WriteString(name);
                        serializer.WriteFloat(value);
                    }
                    break;
                }
                case MeowEngine::CLASS_OR_STRUCT: {
                    if (property.TypeId == typeid(MeowEngine::String)) {
                        auto data = property.Get(instance);
                        MeowEngine::String valueObject = *static_cast<MeowEngine::String*>(data);
                        std::string value = valueObject.GetRawString();

                        std::string name = property.Name;

                        serializer.WriteString(name);
                        serializer.WriteString(value);
                    }
                    else {
                        auto data = property.Get(instance);
                        std::string name = property.TypeName;

                        SerializeClass(serializer, data, name);
                    }


                    break;
                }
                case MeowEngine::POINTER: {

                }
                case MeowEngine::ENUM: {
                    auto data = property.Get(instance);
                    // MeowEngine::Object* dataObject = static_cast<MeowEngine::Object*>(data);
                    std::string name = property.Name;
                    int value = *static_cast<int*>(data);

                    serializer.WriteString(name);
                    serializer.WriteInt(value);
                }
                case MeowEngine::ARRAY: {}
                case MeowEngine::NOT_DEFINED: {}
            }
        }
    }
}

namespace MeowEngine::Runtime {
    void WorldSerializer::Serialize(const FileSystem::Path path, World& world) {
        MeowEngine::Log("WorldSerializer", "Serialize");

        // template world data for testing
        auto testWorld = World();
        auto& registry = testWorld.GetBuffer().GetCurrent();

        entt::entity testEntity = registry.create();
        auto identityComponent = registry.emplace<IdentityComponent>(testEntity);
        auto infoComponent = registry.emplace<entity::InfoComponent>(testEntity);

        identityComponent.SetGUID(5556);
        infoComponent.SetName(String("testEntity"));

        // serialization ahead
        FileSystem::Path filePath = path;
        FileSystem::Path fileName = path.GetName();
        std::shared_ptr<FileSystem::FileStream> stream = std::make_shared<FileSystem::FileStream>();
        // FileSystem::FileStream stream;
        stream->Open(path, FileSystem::FileMode::WRITE);
        Serialization::Serializer serializer {fileName, filePath, stream};

        // save entity count
        size_t entityCount = registry.storage<entt::entity>().size();
        serializer.WriteSize(entityCount);

        // save all guids
        registry.view<IdentityComponent>().each([&serializer](const IdentityComponent& identity) {
            serializer.WriteUInt32(identity.GetGUID());
        });

        // guid, component count, component name & its serialized data (using reflection system)
        registry.view<entt::entity, IdentityComponent>().each([&registry, &serializer](const entt::entity entity, const IdentityComponent& identity) {
            // cache and save entity guid
            const auto guid = identity.GetGUID();
            serializer.WriteUInt32(guid);

            // count components (not the best way)
            uint16_t componentCount = 0;

            // use && for reference (as it is unknown type & we want reference not a copy
            for (auto&& [id, component]: registry.storage()) {
                if (component.contains(entity)) {
                    componentCount++;
                }
            }

            // save component counts
            serializer.WriteUInt16(componentCount);

            // serialize & save component data
            // component = vector storage of that component for every entity using it
            for (auto&& [id, component]: registry.storage()) {
                if (component.contains(entity)) {
                    const entt::id_type type = id;
                    const std::string componentName = MeowEngine::GetReflection().GetComponentName(type);
                    serializer.WriteString(componentName);

                    // properties
                    void* componentObject = component.value(entity);
                    ::SerializeClass(serializer, componentObject, componentName);
                }
            }
        });

        stream->Flush();
        stream->Close();

    }

    void WorldSerializer::Deserialize(const FileSystem::Path path, World& world) {
        // auto& registry = world.GetRegistry();
        // registry.emplace<type>(entity, data);
        // auto entity = registry.create();

        // TEST(registry, "InfoComponent", entity, "Torus")
        // AddComponent<entity::InfoComponent>(registry, entity, "Torus");

        // std::string abc = "ds";
        // void* test1 = &abc;

        // AddComponentMap["InfoComponent"](registry, entity, test1);

        // auto testWorld = World();
        auto& registry = world.GetBuffer().GetCurrent();

        FileSystem::Path worldPath = MeowService().Project.Settings.GetSandboxRootPathE() + "world.meowdata";
        std::shared_ptr<FileSystem::FileStream> stream = std::make_shared<FileSystem::FileStream>();
        stream->Open(worldPath, FileSystem::FileMode::READ);

        FileSystem::Path filePath = path;
        FileSystem::Path fileName = path.GetName();
        Serialization::Serializer serializer {fileName, filePath, stream};

        size_t entityCount;
        entityCount = serializer.ReadSize();
        // stream.Read(&entityCount, sizeof(size_t));
        MeowEngine::Log("Deserialize", (int)entityCount);

        for (auto i = 0; i < entityCount; i++) {
            auto entity = world.GetBuffer().AddEntity();
            world.GetBuffer().AddComponent<IdentityComponent>(entity);
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
    }
}
