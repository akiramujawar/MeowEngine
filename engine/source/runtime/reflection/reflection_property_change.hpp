//
// Created by Akira Mujawar on 11/01/25.
//

#ifndef MEOWENGINE_REFLECTION_PROPERTY_CHANGE_HPP
#define MEOWENGINE_REFLECTION_PROPERTY_CHANGE_HPP

#include "entt.hpp"
#include "reflection_property.hpp"
#include "EntityHandle.hpp"
#include "EntityComponent.hpp"

namespace MeowEngine {
    class ReflectionPropertyChange {
    private:
        ReflectionPropertyChange() {}
    public:
        /**
         *
         * @param inPropertyChangeName
         * @param inChangeData
         * @param inDataDeleter after utilising for changes, this callback destroys the temporary holder of values
         */
        ReflectionPropertyChange(const std::string& inPropertyChangeName, void* inChangeData, std::function<void(void*)> inDataDeleter);
        ~ReflectionPropertyChange();

        static void Assign(ReflectionPropertyChange*& inTarget, ReflectionPropertyChange* inValue) {
            if(inValue != nullptr) {
                inTarget = inValue;
            }
        }

        // int EntityId;
        Runtime::EntityHandle Handle;
        Runtime::EntityComponent ComponentType;
        std::string PropertyName;
        std::vector <ReflectionProperty> ClassProperties;
        void* Data;
        std::function<void(void*)> DataDeleter;
    };
}

#endif //MEOWENGINE_REFLECTION_PROPERTY_CHANGE_HPP
