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
            auto service = new MeowService {
                me.AssetManager,
                me.ConfigManager,
                me.WorldManager,
                me.CommandQueue,
                me.RequestQueue,
                me.Editor
            };

            Instance = service;
        }

        inline static MeowService* Instance = nullptr;

    public:
        Asset::AssetManager& AssetManager;
        Runtime::ConfigManager& ConfigManager;
        Runtime::WorldManager& WorldManager;

        Messaging::CommandQueue& CommandQueue;
        Messaging::RequestQueue& RequestQueue;

        Editor::EditorModule& Editor;
    };

    inline MeowService& MeowService() {
        return MeowService::Get();
    }
}

#endif //MEOWENGINE_ENGINESERVICE_HPP