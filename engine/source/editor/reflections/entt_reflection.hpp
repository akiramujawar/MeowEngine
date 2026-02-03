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
            MeowEngine::Log("Reflection", "Constructed");
        }
        ~EnttReflection() {
            MeowEngine::Log("Reflection", "Destructed");
        }

        bool HasComponent(entt::id_type inId);
        bool HasProperty(std::string inPropertyName);
        bool HasEnum(std::string inPropertyName);

        std::string GetComponentName(entt::id_type inId);
        std::vector<ReflectionProperty> GetProperties(std::string inClassName);
        std::vector<std::string> GetEnumValues(std:: string pEnumName);

        template<typename Type>
        void Reflect();

        // Register types (these are extended by macros in wrapper class)
        void RegisterComponent(entt::id_type inId,  std::string inName);

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
         * @param inClassName
         * @param inPropertyChange
         * @param inClassObject
         */
        void UpdatePropertyChangeData(std::string& inClassName, MeowEngine::ReflectionPropertyChange& inPropertyChange, void* inClassObject) {
            std::vector<MeowEngine::ReflectionProperty> properties = GetProperties(inClassName);

            for(const MeowEngine::ReflectionProperty &property : properties) {
                if(property.Name == inPropertyChange.PropertyName) {
                    property.Set(inClassObject, inPropertyChange.Data);
                }
            }
        }

    private:
        std::unordered_map<entt::id_type, std::string> Components;
        std::unordered_map<std::string, std::vector<ReflectionProperty>> Properties;
        std::unordered_map<std::string, std::vector<std::string>> Enums;
    };

    template<typename Type>
    void EnttReflection::Reflect() {
        if constexpr (std::is_fundamental_v<Type>) {
//            return PropertyType::PRIMITIVE;
        }
        else if constexpr (std::is_array_v<Type>) {
//            return PropertyType::ARRAY;
        }
        else if constexpr (std::is_class_v<Type>) {
            Type::Reflect();
        }
        else {
//            return PropertyType::NOT_DEFINED;
        }
    }
}


#endif //MEOWENGINE_ENTT_REFLECTION_HPP
