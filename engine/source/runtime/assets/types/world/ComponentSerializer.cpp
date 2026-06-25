//
// Created by Akira Mujawar on 17/06/26.
//

#include "ComponentSerializer.hpp"

#include "Public/IO/Include.hpp"


namespace MeowEngine::Asset {

    void ComponentSerializer::Serialize(Serialization::Serializer& serializer, void* instance, const std::string& className) {
        MeowEngine::Log("ComponentSerializer::Serialize", "Started");

        auto properties = GetReflection().GetProperties(className);
        serializer.WriteSize(properties.size());
        for (auto& property : properties) {
            serializer.WriteInt(static_cast<int>(property.Type));
            serializer.WriteString(property.Name);
            serializer.WriteString(property.TypeName);

            switch (property.Type) {
                case PropertyType::PRIMITIVE: {
                    auto data = property.Get(instance);
                    if (property.TypeId == typeid(int)) {
                        int value = *static_cast<int*>(data);
                        serializer.WriteInt(value);
                    }
                    else if (property.TypeId == typeid(float)) {
                        float value = *static_cast<float*>(data);
                        serializer.WriteFloat(value);
                    }
                    else if (property.TypeId == typeid(uint64_t)) {
                        uint64_t value = *static_cast<uint64_t*>(data);
                        serializer.WriteUInt64(value);
                    }
                    else if (property.TypeId == typeid(bool)) {
                        bool value = *static_cast<bool*>(data);
                        serializer.WriteBool(value);
                    }
                    break;
                }
                case PropertyType::CLASS_OR_STRUCT: {
                    auto data = property.Get(instance);
                    if (property.TypeId == typeid(String)) {
                        auto valueObject = *static_cast<String*>(data);
                        auto value = valueObject.GetRawString();
                        serializer.WriteString(value);
                    }
                    else {
                        Serialize(serializer, data, property.TypeName);
                    }
                    break;
                }
                case PropertyType::POINTER: {
                    break;
                }
                case PropertyType::ENUM: {
                    auto data = property.Get(instance);
                    if (property.TypeId == typeid(Runtime::EntityID)) {
                        std::uint64_t value = *static_cast<std::uint64_t*>(data);
                        serializer.WriteUInt64(value);
                    }
                    // if (property.TypeId == typeid(As)) { // asset id
                    //
                    // }
                    else {
                        int value = *static_cast<int*>(data);
                        serializer.WriteInt(value);
                    }

                    break;
                }
                case PropertyType::ARRAY: {

                    break;
                }
                case PropertyType::NOT_DEFINED: {}
            }
        }
    }

    void ComponentSerializer::Deserialize(Serialization::Serializer& serializer, World& world, void* instance, const std::string&  className) {
        MeowEngine::Log("ComponentSerializer::Deserialize", "Started");

        // properties
        auto properties = GetReflection().GetProperties(className);
        auto propertyCount = serializer.ReadSize();
        for (int i = 0 ; i < propertyCount ; i++) {
            auto type = static_cast<PropertyType>(serializer.ReadInt());
            auto propertyName = serializer.ReadString();
            auto typeName = serializer.ReadString();

            ReflectionProperty* property = GetReflection().GetProperty(className, propertyName);

            // deserialize need to happen even if property doesn't exist
            switch (type) {
                case PropertyType::PRIMITIVE: {
                    if (typeName == "int") {
                        auto value = serializer.ReadInt();
                        if (property != nullptr) {
                            property->Set(instance, &value);
                        }
                    }
                    else if (typeName == "float") {
                        auto value = serializer.ReadFloat();
                        if (property != nullptr) {
                            property->Set(instance, &value);
                        }
                    }
                    else if (typeName == "uint64_t") {
                        auto value = serializer.ReadUInt64();
                        if (property != nullptr) {
                            property->Set(instance, &value);
                        }
                    }
                    else if (typeName == "bool") {
                        auto value = serializer.ReadBool();
                        if (property != nullptr) {
                            property->Set(instance, &value);
                        }
                    }

                    break;
                }
                case PropertyType::CLASS_OR_STRUCT: {
                    if (typeName == "String") {
                        auto data = serializer.ReadString();
                        auto stringValue = String(data);
                        if (property != nullptr) {
                            property->Set(instance, &stringValue);
                        }
                    }
                    else {
                        auto data = property->Get(instance);

                        Deserialize(serializer, world, data, typeName);
                    }

                    break;
                }
                case PropertyType::POINTER: {
                    break;
                }
                case PropertyType::ENUM: {
                    if (typeName == "EntityID" || typeName == "AssetID") {
                        auto value = serializer.ReadUInt64();
                        if (property != nullptr) {
                            property->Set(instance, &value);
                        }
                    }
                    else {
                        auto value = serializer.ReadInt();
                        if (property != nullptr) {
                            property->Set(instance, &value);
                        }
                    }

                    break;
                }
                case PropertyType::ARRAY: {
                    break;
                }
                case PropertyType::NOT_DEFINED: {}
                default:
                    break;
            }

        }

        // NOTE: Special case to reference runtime entities
        if (className == "EntityHandle") {
            auto* handle = static_cast<Runtime::EntityHandle*>(instance);
            auto runtimeHandle = world.GetHandle(handle->GetGUID());

            handle->SetEntity(runtimeHandle.GetEntity());
        }

    }
}
