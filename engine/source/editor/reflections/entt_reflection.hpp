//
// Created by Akira Mujawar on 08/01/25.
//

#ifndef MEOWENGINE_ENTT_REFLECTION_HPP
#define MEOWENGINE_ENTT_REFLECTION_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include <magic_enum.hpp>
#include "EntityRegistry.hpp"

#include <log.hpp>

#include <ReflectComponent.hpp>
#include <reflection_property.hpp>
#include <reflection_property_change.hpp>

#include "World.hpp"
#include <functional>

using namespace std;

namespace MeowEngine {
    /**
     *
     */
    using GetOrAddComponentCallback = std::function<void*(Asset::World&, const Runtime::EntityHandle&)>;

    class EnttReflection {

    public:
        EnttReflection() {
            MeowEngine::Log("EnttReflection", "Constructed");
        }
        ~EnttReflection() {
            MeowEngine::Log("EnttReflection", "Destructed");
        }

        bool HasComponent(Runtime::EntityComponent inId);
        bool HasProperty(std::string inPropertyName);
        bool HasEnum(std::string inPropertyName);

        std::string GetComponentName(Runtime::EntityComponent inId);
        std::vector<std::string> GetComponentNames();
        std::vector<ReflectionProperty> GetProperties(std::string inClassName);
        std::vector<std::string> GetEnumValues(std:: string pEnumName);
        ReflectionProperty* GetProperty(const std::string& className, const std::string& propertyName);

        // Register types (these are extended by macros in wrapper class)
        template<typename Type>
        void RegisterComponent(ReflectionComponent inComponent) {
            MeowEngine::Log("RegisterComponent", inComponent.ClassName);

            Runtime::EntityComponent componentId = entt::type_hash<Type>().value();

            if(!HasComponent(componentId)) {
                RuntimeComponentMap[componentId] = inComponent;
                RuntimeComponentNames.push_back(inComponent.ClassName);
            }

            GetOrAddComponentCallbackMap.try_emplace(inComponent.ClassName, &Asset::World::GetOrAddComponentToWorld<Type>);
        }

        /**
         * Registers properties which are to be displayed
         * @param inClassName
         * @param inProperty
         */
        void RegisterProperty(std::string inClassName, ReflectionProperty inProperty);

        template<typename Type>
        void RegisterEnum(const std::string& inEnumName) {
            MeowEngine::Log("RegisterEnum", inEnumName);
            // gets all the enums in array<string_view, num>
            auto names = magic_enum::enum_names<Type>();

            // push each name into our registry of enums
            for(auto & i : names){
                Enums[inEnumName].push_back(i.data());
            }
        }

        void ApplyPropertyChange(ReflectionPropertyChange& inPropertyChange, Runtime::EntityHandle handle, Runtime::EntityRegistry& inRegistry);

        /**
         * Retrieves the all the properties within object from data using reflection storage
         * and applies the change only to the specific item on which the change is required
         * @param pComponentName
         * @param pPropertyAffectedName The root property name from component which is modified. This helps to find & call the callback registered within components
         * @param pComponentData
         * @param pChangedName
         * @param inPropertyChange The container in which the property is affected. Can be component or child classes/structs
         * @param inChangedData
         */
        void UpdatePropertyChangeData(
            std::string& pComponentName,
            std::string& pPropertyAffectedName,
            void* pComponentData,
            std::string& pChangedName,
            MeowEngine::ReflectionPropertyChange& inPropertyChange,
            void* inChangedData
        );

        void* CopyComponentData(Runtime::EntityComponent type, const std::string& name, void* from);
        void DeleteComponentData(Runtime::EntityComponent type, void* from);

        void CopyPropertyData(const std::string& className, void* to, void* from);

        GetOrAddComponentCallback GetGetOrAddComponentCallback(const std::string& componentName) {
            auto iterator = GetOrAddComponentCallbackMap.find(componentName);
            if (iterator != GetOrAddComponentCallbackMap.end()) {
                return iterator->second;
            }

            return nullptr;
        }

    private:
        /**
         * component and methods to perform actions on component (like fresh construction)
         */
        std::unordered_map<Runtime::EntityComponent, ReflectionComponent> RuntimeComponentMap;

        std::vector<std::string> RuntimeComponentNames;

        /**
         *
         */
        std::unordered_map<std::string, GetOrAddComponentCallback> GetOrAddComponentCallbackMap;

        /**
         * class name, reflected property list
         */
        std::unordered_map<std::string, std::vector<ReflectionProperty>> Properties;

        /**
         * class name, reflected enum list containing list of enum string names
         */
        std::unordered_map<std::string, std::vector<std::string>> Enums;

    };

}


#endif //MEOWENGINE_ENTT_REFLECTION_HPP
