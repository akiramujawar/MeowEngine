//
// Created by Akira Mujawar on 16/05/26.
//

#ifndef MEOWENGINE_UIRENDERER_HPP
#define MEOWENGINE_UIRENDERER_HPP

#include <Public/Threading/Include.hpp>

#include <IUIRender.hpp>
#include <InputEvents.hpp>
#include <EditorUIBuilder.hpp>
#include <RuntimeUIBuilder.hpp>

namespace MeowEngine::Input {
    class InputDevice;
}

namespace MeowEngine::Rendering {
    struct RendererInitData;
    struct RenderContext;

    class UIRenderer {
    public:
        UIRenderer();
        ~UIRenderer();

        void Init(RendererInitData& context);
        void SubscribeToEvents();
        void Schedule(Threading::Scheduler& scheduler, RenderContext& renderContext);
        void Shutdown();

    private:
        void ProcessDeviceInput(const Input::InputEvents& events);

    private:
        std::unique_ptr<IUIRender> Backend;

        Runtime::RuntimeUIBuilder RuntimeBuilder;
        Editor::EditorUIBuilder EditorBuilder;

        Input::InputDevice* InputDevice;
    };
}


#endif //MEOWENGINE_UIRENDERER_HPP