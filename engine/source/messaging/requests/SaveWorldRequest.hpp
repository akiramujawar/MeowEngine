//
// Created by Akira Mujawar on 18/06/26.
//

#ifndef MEOWENGINE_SAVEWORLDREQUEST_HPP
#define MEOWENGINE_SAVEWORLDREQUEST_HPP

#include <string>

#include "IRequest.hpp"
#include "AssetHandle.hpp"

namespace MeowEngine::Messaging {
    class SaveWorldRequest : public IRequest {
    public:
        SaveWorldRequest(const Asset::AssetHandle& handle);
        // ~SaveWorldRequest() override;

        bool ExecuteRequest(MessageInitData& context) override;
        void ExecuteResponse(MessageInitData& context) override;

    private:
        std::string DirectoryPath;
        Asset::AssetHandle WorldHandle;
    };
}


#endif //MEOWENGINE_SAVEWORLDREQUEST_HPP