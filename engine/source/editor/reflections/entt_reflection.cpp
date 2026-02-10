//
// Created by Akira Mujawar on 08/01/25.
//

#include "entt_reflection.hpp"

#include "m_object.hpp"
#include "log.hpp"
#include "pstring.hpp"

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

void MeowEngine::EnttReflection::RegisterProperty(std::string inClassName, ReflectionProperty inProperty) {
    // TODO: throw a warning if a property already exists
    // MeowEngine::Log("RegisterProperty", {inClassName, inProperty.Name}, MeowEngine::LogType::WARNING);

    Properties[inClassName].push_back(inProperty);
}

void MeowEngine::EnttReflection::ApplyPropertyChange(MeowEngine::ReflectionPropertyChange& inPropertyChange, entt::registry& inRegistry) {
    auto changedEntity = static_cast<entt::entity>(inPropertyChange.EntityId);

    entt::basic_registry<>::common_type *componentStorage = inRegistry.storage(inPropertyChange.ComponentType);
    std::string componentName = GetComponentName(inPropertyChange.ComponentType);

    void* componentObject = componentStorage->value(changedEntity);
    void* data = componentStorage->value(changedEntity);

    // if component has direct changes
    if(inPropertyChange.ClassProperties.empty()) {
        UpdatePropertyChangeData(componentName, inPropertyChange.PropertyName, componentObject, componentName, inPropertyChange, data);
    }
    // if classes / struct / pointers within component has changes
    else {
        int classPropertyCount = (int)inPropertyChange.ClassProperties.size() - 1;
        std::string propertyAffectedName = inPropertyChange.ClassProperties[classPropertyCount].Name;

        // retrieve the final object of changed property,
        // essentially navigates from root node to final node (like a tree)
        for(int i = classPropertyCount ; i > 0 ; i--) {
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

                UpdatePropertyChangeData(componentName, propertyAffectedName, componentObject, className, inPropertyChange, objectData);
            }
            catch (...) {
                throw;
            }
        }
        // send objects as they are within component storage
        else {
            UpdatePropertyChangeData(componentName, propertyAffectedName, componentObject, changedProperty.TypeName, inPropertyChange, data);
        }

    }
}

void MeowEngine::EnttReflection::UpdatePropertyChangeData(std::string& pComponentName, std::string& pPropertyAffectedName, void* pComponentData, std::string& pChangedName, MeowEngine::ReflectionPropertyChange& inPropertyChange, void* inChangedData) {
    // Update the value which is affected
    std::vector<MeowEngine::ReflectionProperty> propertiesFromChanged = GetProperties(pChangedName);
    for(const MeowEngine::ReflectionProperty &property : propertiesFromChanged) {
        if(property.Name == inPropertyChange.PropertyName) {
            property.Set(inChangedData, inPropertyChange.Data);
            break;
        }
    }

    // Call the callback registered at component level for the specific property
    std::vector<MeowEngine::ReflectionProperty> propertiesFromComponent = GetProperties(pComponentName);
    for(const MeowEngine::ReflectionProperty &property : propertiesFromComponent) {
        if(property.Name == pPropertyAffectedName) {
            property.Callback(pComponentData);
            break;
        }
    }
}