//
// Created by Akira Mujawar on 14/05/26.
//

#include <RenderCommand.hpp>

#include <GLRenderAPI.hpp>

namespace MeowEngine::Rendering {
    void RenderCommand::Init(const GraphicsAPI type) {
        switch (type) {
            case GraphicsAPI::None:
                break;
            case GraphicsAPI::OPENGL:
                Command = std::make_unique<GLRenderAPI>();
                break;
            case GraphicsAPI::VULKAN:
                break;
        }
    }

    void RenderCommand::Clear() {
        Command->Clear();
    }

    std::unique_ptr<IRenderAPI> RenderCommand::Command = nullptr;
}
