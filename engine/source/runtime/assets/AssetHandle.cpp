//
// Created by Akira Mujawar on 11/03/26.
//

#include <AssetHandle.hpp>

namespace MeowEngine::Runtime::Asset {

    AssetHandle::AssetHandle() {}

    AssetHandle::~AssetHandle() {}

    bool AssetHandle::IsValid() const {
        return true;
    }

    uint64_t AssetHandle::GetUUID() const {
        return UUID;
    }

    bool AssetHandle::operator==(const AssetHandle& handle) const {
        return UUID == handle.UUID;
    }

    bool AssetHandle::operator!=(const AssetHandle& handle) const {
        return UUID != handle.UUID;
    }

}
