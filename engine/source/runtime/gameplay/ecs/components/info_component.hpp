//
// Created by Akira Mujawar on 01/08/24.
//

#ifndef MEOWENGINE_INFO_COMPONENT_HPP
#define MEOWENGINE_INFO_COMPONENT_HPP

#include <String.hpp>
#include <ComponentBase.hpp>

namespace MeowEngine::Runtime {
    struct InfoComponent : public MeowEngine::Runtime::ComponentBase {
    public:
        REFLECT_COMPONENT(InfoComponent)
        static void Reflect();

        InfoComponent();
        InfoComponent(std::string name);

        void SetName(const String& name);
        [[nodiscard]] String GetName() const;

        String Name;
    };
}


#endif //MEOWENGINE_INFO_COMPONENT_HPP
