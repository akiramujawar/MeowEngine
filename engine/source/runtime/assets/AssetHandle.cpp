//
// Created by Akira Mujawar on 11/03/26.
//

#include <AssetHandle.hpp>

namespace MeowEngine::Asset {
    void AssetHandle::Reflect()  {
        REGISTER_PROPERTY(AssetHandle, UUID, uint64_t, true, true);
        REGISTER_PROPERTY(AssetHandle, IsTemp, bool, true, true);
        REGISTER_PROPERTY(AssetHandle, IsValid, bool, true, true);
    }

    AssetHandle AssetHandle::Invalid = AssetHandle::CreateInvalid();

    AssetHandle::AssetHandle()
        : UUID(-1) ,
        IsTemp(false) ,
        IsValid(false)
    {}

    bool AssetHandle::GetIsValid() const {
        return IsValid;
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
