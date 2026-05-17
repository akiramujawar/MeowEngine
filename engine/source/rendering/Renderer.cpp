//
// Created by Akira Mujawar on 17/05/26.
//

#include "Renderer.hpp"

#include <RendererContext.hpp>

namespace MeowEngine::Rendering {
    Renderer::Renderer() {}
    Renderer::~Renderer() {}
    void Renderer::Init(RendererContext& context) {
        World.Init(context);
        UI.Init(context);

        Device = context.Device;
    }

    void Renderer::Schedule(Threading::Scheduler& scheduler) {
        World.Schedule(scheduler);
        UI.Schedule(scheduler);

        scheduler.AddTask(
            [&window = Device->GetWindow()]() {
                window.SwapWindow();
            }
        );
    }
}
