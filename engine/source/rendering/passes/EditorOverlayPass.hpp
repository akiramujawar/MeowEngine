//
// Created by Akira Mujawar on 19/05/26.
//

#ifndef MEOWENGINE_EDITOROVERLAYPASS_HPP
#define MEOWENGINE_EDITOROVERLAYPASS_HPP

// selection outlines
// grid

#include <IRenderPass.hpp>

namespace MeowEngine::Rendering {
    class EditorOverlayPass : IRenderPass {
    public:
        EditorOverlayPass();
        ~EditorOverlayPass() override;

        void Draw(RenderContext& context) override;
    };
}

#endif //MEOWENGINE_EDITOROVERLAYPASS_HPP