//
// Created by Akira Mujawar on 16/05/26.
//

#ifndef MEOWENGINE_UIRENDERER_HPP
#define MEOWENGINE_UIRENDERER_HPP

#include <Public/Threading/Include.hpp>

#include <IUIRender.hpp>
#include <EditorUIBuilder.hpp>
#include <RuntimeUIBuilder.hpp>

namespace MeowEngine::Rendering {
    struct RendererInitData;

    class UIRenderer {
    public:
        UIRenderer();
        ~UIRenderer();

        void Init(RendererInitData& context);
        void Schedule(Threading::Scheduler& scheduler);

    private:
        std::unique_ptr<IUIRender> Backend;

        Runtime::RuntimeUIBuilder RuntimeBuilder;
        Editor::EditorUIBuilder EditorBuilder;
    };
}


#endif //MEOWENGINE_UIRENDERER_HPP