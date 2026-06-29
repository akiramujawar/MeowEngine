//
// Created by Akira Mujawar on 08/01/25.
//

#include "entt_reflection.hpp"

#include "AssetHandle.hpp"
#include "Public/Core/Include.hpp"
#include "Public/Math.hpp"
#include "log.hpp"

namespace MeowEngine {

    bool EnttReflection::HasComponent(Runtime::ComponentID inId) {
        return RuntimeComponentMap.find(inId) != RuntimeComponentMap.end();
    }

    bool EnttReflection::HasProperty(std::string inPropertyName) {
        return Properties.find(inPropertyName) != Properties.end();
    }

    bool EnttReflection::HasEnum(std::string inPropertyName) {
        return Enums.find(inPropertyName) != Enums.end();
    }

    std::string EnttReflection::GetComponentName(Runtime::ComponentID inId) {
        return RuntimeComponentMap[inId].ClassName;
    }

    std::vector<std::string> EnttReflection::GetComponentNames() {
        return RuntimeComponentNames;
    }

    std::vector<ReflectionProperty> EnttReflection::GetProperties(std::string inClassName) {
        return Properties[inClassName];
    }

    std::vector<std::string> EnttReflection::GetEnumValues(std::string pEnumName) {
        return Enums[pEnumName];
    }

    ReflectionProperty* EnttReflection::GetProperty(const std::string& className, const std::string& propertyName) {
        for (auto& property : Properties[className]) {
            if (property.Name == propertyName) {
                return &property;
            }
        }

        return nullptr;
    }

    void EnttReflection::RegisterProperty(std::string inClassName, ReflectionProperty inProperty) {
        // TODO: throw a warning if a property already exists
        // MeowEngine::Log("RegisterProperty", {inClassName, inProperty.Name}, MeowEngine::LogType::WARNING);

        Properties[inClassName].push_back(inProperty);
    }

    void EnttReflection::ApplyPropertyChange(ReflectionPropertyChange& inPropertyChange, Runtime::EntityHandle handle, Runtime::EntityRegistry& inRegistry) {
        auto entity = handle.GetEntity();
        entt::basic_registry<Runtime::Entity>::common_type *componentStorage = inRegistry.storage(inPropertyChange.ComponentType);
        std::string componentName = GetComponentName(inPropertyChange.ComponentType);

        void* componentObject = componentStorage->value(entity);
        void* data = componentStorage->value(entity);

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
                    Object *dataObject = *static_cast<Object **>(data); // object
                    data = dataObject;
                }
            }

            // not to confuse. change property is a holder in which a property is updated
            MeowEngine::ReflectionProperty changedProperty = inPropertyChange.ClassProperties[0];
            data = changedProperty.Get(data);

            if(changedProperty.Type == MeowEngine::PropertyType::POINTER) {
                // dereference for pointers to point towards correct address
                auto objectPointer = static_cast<Object **>(data);
                Object* objectData = *objectPointer;

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

    void EnttReflection::UpdatePropertyChangeData(std::string& pComponentName, std::string& pPropertyAffectedName, void* pComponentData, std::string& pChangedName, MeowEngine::ReflectionPropertyChange& inPropertyChange, void* inChangedData) {
        // Update the value which is affected
        std::vector<MeowEngine::ReflectionProperty> propertiesFromChanged = GetProperties(pChangedName);
        for(const MeowEngine::ReflectionProperty &property : propertiesFromChanged) {
            if(property.Name == inPropertyChange.PropertyName) {
                Asset::AssetHandle* assetHandle = static_cast<Asset::AssetHandle*>(inPropertyChange.Data);
                property.Set(inChangedData, inPropertyChange.Data);
                break;
            }
        }

        // TODO: This is temporary. After making the change, we need to recursively go from component to changed property and execute callbacks
        // start ---
        // Call the callback registered at component level for the specific property
        // This only happens for parent level. Not so good.
        std::vector<MeowEngine::ReflectionProperty> propertiesFromComponent = GetProperties(pComponentName);
        for(const MeowEngine::ReflectionProperty &property : propertiesFromComponent) {
            if(property.Name == pPropertyAffectedName) {
                property.Callback(pComponentData);
                break;
            }
        }

        std::vector<MeowEngine::ReflectionProperty> propertiesFromObject = GetProperties(pChangedName);
        for(const auto& property : propertiesFromObject) {
            if(property.Name == inPropertyChange.PropertyName) {
                property.Callback(inChangedData);
                break;
            }
        }
        // end --
    }

    void* EnttReflection::CopyComponentData(Runtime::ComponentID type, const std::string& name, void* from) {
        void* to = RuntimeComponentMap[type].Construct();

        CopyPropertyData(name, to, from);

        return to;
    }

    void EnttReflection::DeleteComponentData(Runtime::ComponentID type, void* from) {
        RuntimeComponentMap[type].Destruct(from);
    }

    void EnttReflection::CopyPropertyData(const std::string& className, void* to, void* from) {
        const auto properties = GetProperties(className);
        for (const auto& property : properties) {

            // need to handle primitives, struct / classes & enums, pointers

            switch(property.Type) {
                case PropertyType::NOT_DEFINED:
                    break;
                case PropertyType::PRIMITIVE: {
                    auto data = property.Get(from);
                    property.Set(to, data);

                    break;
                }
                case PropertyType::ARRAY:
                    break;
                case PropertyType::POINTER: {
                    if (property.IsMObject) {
                        void* toPointer = property.Get(to);
                        void* fromPointer = property.Get(from);

                        Object* toObject = *static_cast<Object**>(toPointer) ;
                        Object* fromObject = *static_cast<Object**>(fromPointer) ;

                        if (fromObject != nullptr) {
                            CopyPropertyData(fromObject->GetClassName(), toObject, fromObject);
                        }
                    }
                }
                    break;
                case PropertyType::ENUM: {
                    auto data = property.Get(from);
                    property.Set(to, data);

                    break;
                }
                    break;
                case PropertyType::CLASS_OR_STRUCT: {
                    if (property.TypeId == typeid(String) ||
                        property.TypeId == typeid(Vector3) ||
                        property.TypeId == typeid(Quaternion) ||
                        property.TypeId == typeid(Runtime::EntityHandle) ||
                        property.TypeId == typeid(Asset::AssetHandle))
                    {
                        auto data = property.Get(from);
                        property.Set(to, data);
                    }
                    else {
                        if (property.IsMObject) {
                            CopyPropertyData(property.TypeName, property.Get(to), property.Get(from));
                        }
                    }
                    break;
                }
            }
        }
    }
}
