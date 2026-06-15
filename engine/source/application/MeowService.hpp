//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_ENGINESERVICE_HPP
#define MEOWENGINE_ENGINESERVICE_HPP

#include <cassert>

#include "MeowServiceInitData.hpp"

// -- class ----------------
namespace MeowEngine {
    struct Engine;
    struct MeowService {
        friend Engine;

        static MeowService& Get() {
            assert(Instance); // cannot support on emscripten :(
            return *Instance;
        }

        // delete copy & assign
        MeowService(const MeowService&) = delete;
        MeowService& operator=(const MeowService&) = delete;

    private:
        static void Init(MeowServiceInitData& me) {
            auto t = new MeowService {
                me.AssetManager,
                me.Project,
                me.Editor
            };

            Instance = t;
        }

        inline static MeowService* Instance = nullptr;

    public:
        Asset::AssetManager& AssetManager;
        Runtime::Project& Project;
        Editor::EditorModule& Editor;
    };

    inline MeowService& MeowService() {
        return MeowService::Get();
    }
}

#endif //MEOWENGINE_ENGINESERVICE_HPP