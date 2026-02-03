//
// Created by Akira Mujawar on 08/01/25.
//

#include "entt_reflection.hpp"

#include "log.hpp"

bool MeowEngine::EnttReflection::HasComponent(entt::id_type inId) {
    return Components.find(inId) != Components.end();
}

bool MeowEngine::EnttReflection::HasProperty(std::string inPropertyName) {
    return Properties.find(inPropertyName) != Properties.end();
}

bool MeowEngine::EnttReflection::HasEnum(std::string inPropertyName) {
    return Enums.find(inPropertyName) != Enums.end();
}

std::string MeowEngine::EnttReflection::GetComponentName(entt::id_type inId) {
    return Components[inId];
}

std::vector<MeowEngine::ReflectionProperty> MeowEngine::EnttReflection::GetProperties(std::string inClassName) {
    return Properties[inClassName];
}

std::vector<std::string> MeowEngine::EnttReflection::GetEnumValues(std::string pEnumName) {
    return Enums[pEnumName];
}

void MeowEngine::EnttReflection::RegisterComponent(entt::id_type inId, std::string inName) {
    if(!HasComponent(inId)) {
//        Components.insert_or_assign(inId, inName);
        Components[inId] = inName;
    }
}

void MeowEngine::EnttReflection::RegisterProperty(std::string inClassName, ReflectionProperty inProperty) {
//    if(!HasProperty(inClassName)) {
        Properties[inClassName].push_back(inProperty);
//    }
}

void MeowEngine::EnttReflection::ApplyPropertyChange(MeowEngine::ReflectionPropertyChange& inPropertyChange, entt::registry& inRegistry) {
    auto changedEntity = static_cast<entt::entity>(inPropertyChange.EntityId);

    entt::basic_registry<>::common_type *componentStorage = inRegistry.storage(inPropertyChange.ComponentType);
    std::string componentName = GetComponentName(inPropertyChange.ComponentType);

    void* data = componentStorage->value(changedEntity);

    // if component has direct changes
    if(inPropertyChange.ClassProperties.empty()) {
        UpdatePropertyChangeData(componentName, inPropertyChange, data);
    }
    // if classes / struct / pointers within component has changes
    else {
        for(int i = inPropertyChange.ClassProperties.size() - 1; i >= 0; i--) {
            // we navigate from top to bottom;
            // i.e. component to variables within, to reach the final object we need to apply the modifications on
            MeowEngine::ReflectionProperty property = inPropertyChange.ClassProperties[i];
            data = property.Get(data);

            // TODO: check back on this, i am worried this might lead to copy entire class/structure
            // leading to erasure of pointers, thus memory leaks
            if(i == 0) {
                if(property.Type == MeowEngine::PropertyType::POINTER) {
                    // dereference for pointers to point towards correct address
                    auto objectPointer = static_cast<MeowEngine::entity::MObject **>(data);
                    MeowEngine::entity::MObject* objectData = *objectPointer;

                    // since the stored typename is a pointer,
                    // we retrieve original class name through internal custom method
                    std::string className = objectData->GetClassName();

                    UpdatePropertyChangeData(className, inPropertyChange, objectData);
                }
                // send objects as they are within component storage
                else {
                    UpdatePropertyChangeData(property.TypeName, inPropertyChange, data);
                }
            }
        }
    }
}