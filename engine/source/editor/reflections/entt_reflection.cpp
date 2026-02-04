//
// Created by Akira Mujawar on 08/01/25.
//

#include "entt_reflection.hpp"

#include "m_object.hpp"
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
        // retrieve the final object of changed property,
        // essentially navigates from root node to final node (like a tree)
        for(int i = (int)inPropertyChange.ClassProperties.size() - 1 ; i > 0 ; i--) {
            MeowEngine::ReflectionProperty property = inPropertyChange.ClassProperties[i];
            // get object data from property
            data = property.Get(data);

            // if its pointer we dereference from pointer to object
            if(property.Type == MeowEngine::PropertyType::POINTER) {
                entity::MObject *dataObject = *static_cast<entity::MObject **>(data); // object
                data = dataObject;
            }
        }

        // not to confuse. change property is a holder in which a property is updated
        MeowEngine::ReflectionProperty changedProperty = inPropertyChange.ClassProperties[0];
        data = changedProperty.Get(data);

        if(changedProperty.Type == MeowEngine::PropertyType::POINTER) {
            // dereference for pointers to point towards correct address
            auto objectPointer = static_cast<MeowEngine::entity::MObject **>(data);
            MeowEngine::entity::MObject* objectData = *objectPointer;

            // this isn't required as no changes will be submitted as null objects / non-MObjects won't be displayed
            // but as fail case, to debug better while building engine we put try catch
            try {
                // since the stored typename is a pointer,
                // we retrieve original class name through internal custom method
                std::string className = objectData->GetClassName();

                UpdatePropertyChangeData(className, inPropertyChange, objectData);
            }
            catch (...) {
                throw;
            }
        }
        // send objects as they are within component storage
        else {
            UpdatePropertyChangeData(changedProperty.TypeName, inPropertyChange, data);
        }

    }
}