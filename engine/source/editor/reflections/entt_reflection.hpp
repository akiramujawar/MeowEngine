//
// Created by Akira Mujawar on 08/01/25.
//

#ifndef MEOWENGINE_ENTT_REFLECTION_HPP
#define MEOWENGINE_ENTT_REFLECTION_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include <magic_enum.hpp>
#include <entt.hpp>

#include <log.hpp>

#include <entt_triple_buffer.hpp>
#include <entt_single_buffer.hpp>

#include <ReflectComponent.hpp>
#include <reflection_property.hpp>
#include <reflection_property_change.hpp>

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
        void RegisterComponent(ReflectionComponent inComponent) {
            MeowEngine::Log("RegisterComponent", inComponent.Name);

            entt::id_type componentId = entt::type_hash<Type>().value();

            if(!HasComponent(componentId)) {
                ComponentMap[componentId] = inComponent;
            }
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

        /**
         * Pointer Method which holds a component template type to be passed to entt buffer
         * for registration
         * The callback is registered in runtime initialisation
         * & executed on engine start (after entt buffer is created)
         * @param pCallback
         */
        void AddInitialiseComponentCallback(void(*pCallback)(void*)) {
            ComponentBufferRegistryCallbacks.push_back(pCallback);
        }

        /**
         * Currently it only initialises components for entt buffer, but as this is called on scene start,
         * we can additionally use this process other things related to components
         */
#ifdef __MULTI_THREAD__
        void InitialiseComponents(MeowEngine::EnttTripleBuffer& pBuffer) {
#elif __SINGLE_THREAD__
        void InitialiseComponents(MeowEngine::EnttSingleBuffer& pBuffer) {
#endif
            for(auto callback : ComponentBufferRegistryCallbacks) {
                callback(&pBuffer);
            }
        }

        /**
         * This is cached in runtime initialisation and the used to register
         * all the components with entt system in a buffer
         *
         * NOTE: this method isn't necessarily required to be a part of entt reflection class
         * @tparam Type
         * @param pEnttBuffer
         */
        template<typename Type>
        static void RegisterComponentOnEnttBuffer(void* pEnttBuffer) {
#ifdef __MULTI_THREAD__
            auto buffer = static_cast<MeowEngine::EnttTripleBuffer*>(pEnttBuffer);
#elif __SINGLE_THREAD__
            auto buffer = static_cast<MeowEngine::EnttSingleBuffer*>(pEnttBuffer);
#endif
            buffer->RegisterComponent<Type>();
        }

        void ApplyPropertyChange(MeowEngine::ReflectionPropertyChange& inPropertyChange, entt::entity entity, entt::registry& inRegistry);

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

        void* CopyComponentData(entt::id_type type, const std::string& name, void* from);

        void CopyPropertyData(const std::string& className, void* to, void* from);

    private:
        /**
         * component and methods to perform actions on component (like fresh construction)
         */
        std::unordered_map<entt::id_type, ReflectionComponent> ComponentMap;

        /**
         * class name, reflected property list
         */
        std::unordered_map<std::string, std::vector<ReflectionProperty>> Properties;

        /**
         * class name, reflected enum list containing list of enum string names
         */
        std::unordered_map<std::string, std::vector<std::string>> Enums;

        std::vector<void(*)(void*)> ComponentBufferRegistryCallbacks;
    };

}


#endif //MEOWENGINE_ENTT_REFLECTION_HPP
