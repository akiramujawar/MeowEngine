//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINETEST2_ASSETHANDLE_HPP
#define MEOWENGINETEST2_ASSETHANDLE_HPP

#include <cstdlib>

namespace MeowEngine::Runtime::Asset {
    /**
     * Container for UUID
     */
    class AssetHandle {
    public:
        AssetHandle();
        ~AssetHandle();

        bool IsValid();
        uint64_t GetUUID();

        bool operator==(const AssetHandle& handle) const;
        bool operator!=(const AssetHandle& handle) const;

    private:
        uint64_t UUID;
    };
}


#endif //MEOWENGINETEST2_ASSETHANDLE_HPP