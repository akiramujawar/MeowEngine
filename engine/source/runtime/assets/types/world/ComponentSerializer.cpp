//
// Created by Akira Mujawar on 17/06/26.
//

#include "ComponentSerializer.hpp"

#include "Public/IO/Include.hpp"


namespace MeowEngine::Asset {

    void ComponentSerializer::Serialize(Serialization::Serializer& serializer, void* instance, const std::string& className) {
        // properties
        auto properties = GetReflection().GetProperties(className);
        for (auto& property : properties) {
            switch (property.Type) {
                case PropertyType::PRIMITIVE: {
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
                case PropertyType::CLASS_OR_STRUCT: {
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

                        Serialize(serializer, data, name);
                    }


                    break;
                }
                case MeowEngine::POINTER: {

                }
                case PropertyType::ENUM: {
                    auto data = property.Get(instance);
                    // MeowEngine::Object* dataObject = static_cast<MeowEngine::Object*>(data);
                    std::string name = property.Name;
                    int value = *static_cast<int*>(data);

                    serializer.WriteString(name);
                    serializer.WriteInt(value);
                }
                case PropertyType::ARRAY: {}
                case PropertyType::NOT_DEFINED: {}
            }
        }
    }

    void ComponentSerializer::Deserialize(Serialization::Serializer& serializer, void* instance, const std::string&  className) {}
}
