//
// Created by Akira Mujawar on 30/06/26.
//

#ifndef MEOWENGINE_IMGUIMAINMENU_HPP
#define MEOWENGINE_IMGUIMAINMENU_HPP

namespace MeowEngine::Rendering {
    struct RenderContext;
}

namespace MeowEngine::Editor {
    class ImguiMainMenu {
    public:
        void Draw(Rendering::RenderContext& renderContext);
    };
}


#endif //MEOWENGINE_IMGUIMAINMENU_HPP