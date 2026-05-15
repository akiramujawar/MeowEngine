//
// Created by Akira Mujawar on 14/05/26.
//

#include <RenderCommand.hpp>

#include <GLRender.hpp>

namespace MeowEngine::Rendering {
    void RenderCommand::Init(const GraphicsType type) {
        switch (type) {
            case GraphicsType::None:
                break;
            case GraphicsType::OPENGL:
                Command = std::make_unique<GLRender>();
                break;
            case GraphicsType::VULKAN:
                break;
        }
    }

    void RenderCommand::Clear() {
        Command->Clear();
    }

    std::unique_ptr<IRenderAPI> RenderCommand::Command = nullptr;
}
