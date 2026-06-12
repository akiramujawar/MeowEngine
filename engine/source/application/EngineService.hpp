//
// Created by Akira Mujawar on 12/06/26.
//

#ifndef MEOWENGINE_ENGINESERVICE_HPP
#define MEOWENGINE_ENGINESERVICE_HPP

namespace MeowEngine {
    namespace Runtime {
        namespace Asset {
            class AssetManager;
        }

        class Project;
    }

    namespace Editor {
        class EditorModule;
    }

    struct EngineService {
        friend struct Engine;

        static EngineService& Get() {
            assert(Instance);
            return *Instance;
        }

        // delete copy & assign
        EngineService(const EngineService&) = delete;
        EngineService& operator=(const EngineService&) = delete;

    private:
        static void Init(EngineService& me) {
            Instance = &me;
        }

        inline static EngineService* Instance = nullptr;

    public:
        Runtime::Asset::AssetManager& AssetManager;
        Runtime::Project& Project;
        Editor::EditorModule& Editor;
    };

    inline EngineService& MeowEngine() {
        return EngineService::Get();
    }
}

#endif //MEOWENGINE_ENGINESERVICE_HPP