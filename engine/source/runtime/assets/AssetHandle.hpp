//
// Created by Akira Mujawar on 11/03/26.
//

#ifndef MEOWENGINE_ASSETHANDLE_HPP
#define MEOWENGINE_ASSETHANDLE_HPP

// #include <cstdlib>
#include <functional>
#include "UUID.hpp"

namespace MeowEngine::Asset {
    /**
     * Container for UUID (pure uuid only)
     * NOTE: Is created internally by AssetRegistry only
     */
    struct AssetHandle {
        AssetHandle();
        ~AssetHandle();

        /**
         * When a reference is not assigned
         */
        static AssetHandle Null;

        [[nodiscard]] bool IsValid() const;
        [[nodiscard]] bool GetIsTemp() const;
        [[nodiscard]] uint64_t GetUUID() const;

        // AssetHandle& operator=(const AssetHandle& handle);
        bool operator==(const AssetHandle& handle) const;
        bool operator!=(const AssetHandle& handle) const;

        static AssetHandle CreateTemp() {
            AssetHandle handle;
            handle.UUID = Core::UUID::GenerateUUID();
            handle.IsTemp = true;

            return handle;
        }

        static AssetHandle Create(uint64_t uuid) {
            AssetHandle handle;
            handle.UUID = uuid;
            handle.IsTemp = false;

            return handle;
        }

    private:
        uint64_t UUID;
        bool IsTemp;
    };
}

namespace std {
    template<>
    struct std::hash<MeowEngine::Asset::AssetHandle> {
        std::size_t operator()(const MeowEngine::Asset::AssetHandle& assetHandle) const noexcept {
            return std::hash<uint64_t>()(assetHandle.GetUUID());
        }
    };
}

#endif //MEOWENGINE_ASSETHANDLE_HPP