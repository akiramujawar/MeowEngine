//
// Created by Akira Mujawar on 08/01/25.
//

#ifndef MEOWENGINE_ENTT_REFLECTION_HPP
#define MEOWENGINE_ENTT_REFLECTION_HPP

#include "unordered_map"
#include "entt_wrapper.hpp"
#include "vector"
#include "reflection_property.hpp"
#include "reflection_property_change.hpp"
#include "string"
#include "log.hpp"

#include "magic_enum.hpp"

using namespace std;

namespace MeowEngine {
    class EnttReflection {

    public:
        EnttReflection() {
            MeowEngine::Log("EnttReflection", "Constructed");
        }
        ~EnttReflection() {
            MeowEngine::Log("EnttReflection", "Destructed");
        }

        bool HasComponent(entt::id_type inId);
        bool HasProperty(std::string inPropertyName);
        bool HasEnum(std::string inPropertyName);

        std::string GetComponentName(entt::id_type inId);
        std::vector<ReflectionProperty> GetProperties(std::string inClassName);
        std::vector<std::string> GetEnumValues(std:: string pEnumName);

        // Register types (these are extended by macros in wrapper class)
        template<typename Type>
        void RegisterComponent(std::string inName) {
            MeowEngine::Log("RegisterComponent", inName);
            entt::id_type componentId = entt::type_hash<Type>().value();
            if(!HasComponent(componentId)) {
                Components[componentId] = inName;
            }
        }

        void RegisterProperty(std::string inClassName, ReflectionProperty inProperty);

        template<typename Type>
        void RegisterEnum(const std::string& inEnumName) {
            // gets all the enums in array<string_view, num>
            auto names = magic_enum::enum_names<Type>();

            // push each name into our registry of enums
            for(auto & i : names){
                Enums[inEnumName].push_back(i.data());
            }
        }

        void ApplyPropertyChange(MeowEngine::ReflectionPropertyChange& inPropertyChange, entt::registry& inRegistry);

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

    private:
        std::unordered_map<entt::id_type, std::string> Components;
        std::unordered_map<std::string, std::vector<ReflectionProperty>> Properties;
        std::unordered_map<std::string, std::vector<std::string>> Enums;
    };

}


#endif //MEOWENGINE_ENTT_REFLECTION_HPP
