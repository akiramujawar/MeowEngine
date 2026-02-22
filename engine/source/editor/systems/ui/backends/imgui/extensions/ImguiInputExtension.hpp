//
// Created by Akira Mujawar on 10/01/25.
//

#ifndef MEOWENGINE_IMGUIINPUTEXTENSION_HPP
#define MEOWENGINE_IMGUIINPUTEXTENSION_HPP

#include "string"
#include "reflection_property.hpp"
#include "reflection_property_change.hpp"

using namespace std;

namespace MeowEngine::Runtime {
    class ImGuiInputExtension {
    public:
        static MeowEngine::ReflectionPropertyChange* ShowProperty(const std::string& inClassName, void* inObject, bool pIsEditable);

        static MeowEngine::ReflectionPropertyChange* ShowPrimitive(const MeowEngine::ReflectionProperty& inProperty, void* inObject, bool pIsEditable);
        static MeowEngine::ReflectionPropertyChange* ShowArray(const MeowEngine::ReflectionProperty& inProperty, void* inObject);
        static MeowEngine::ReflectionPropertyChange* ShowPointer(const MeowEngine::ReflectionProperty& inProperty, void* inObject, bool pIsEditable);
        static MeowEngine::ReflectionPropertyChange* ShowEnum(const MeowEngine::ReflectionProperty& inProperty, void* inObject, bool pIsEditable);
        static MeowEngine::ReflectionPropertyChange* ShowClassOrStruct(const MeowEngine::ReflectionProperty& inProperty, void* inObject, bool pIsEditable);


        static void ShowTabExample();
        static void ShowPushItemWidthExample();
        static void TextInputWithLimitedText(const char* label, float textPercentage, char* inputBuffer, size_t bufferSize);
        static void TextInputWithLimitedTextWrap(const char* label, float textPercentage, char* inputBuffer, size_t bufferSize);
        static void SeparatorTest();
    };
}

#endif //MEOWENGINE_IMGUIINPUTEXTENSION_HPP
