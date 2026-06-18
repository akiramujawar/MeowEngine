//
// Created by Akira Mujawar on 11/03/26.
//

#include <AssetHandle.hpp>

namespace MeowEngine::Asset {

    AssetHandle::AssetHandle() : UUID(-1) , IsTemp(false) {}

    AssetHandle::~AssetHandle() = default;

    AssetHandle AssetHandle::Null = AssetHandle::CreateTemp();

    bool AssetHandle::IsValid() const {
        return true;
    }

    bool AssetHandle::GetIsTemp() const {
        // volatile bool temp = IsTemp;
        return IsTemp;
    }

    uint64_t AssetHandle::GetUUID() const {
        return UUID;
    }

    // AssetHandle& AssetHandle::operator=(const AssetHandle& handle) {
    //     UUID = handle.UUID;
    //     IsTemp = handle.IsTemp;
    //
    //     return *this;
    // }

    bool AssetHandle::operator==(const AssetHandle& handle) const {
        return UUID == handle.UUID;
    }

    bool AssetHandle::operator!=(const AssetHandle& handle) const {
        return UUID != handle.UUID;
    }

}
