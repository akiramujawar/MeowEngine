//
// Created by Akira Mujawar on 19/06/26.
//

#ifndef MEOWENGINE_ENTITYHANDLE_HPP
#define MEOWENGINE_ENTITYHANDLE_HPP

#include <cstdlib>
#include <functional>

#include "Entity.hpp"
#include "EntityID.hpp"

namespace MeowEngine::Asset {
    class World;
}

namespace MeowEngine::Runtime {
    /**
     * Used as reference similar to AssetHandle, RenderHandler, ComponentHandle
     */
    struct EntityHandle {
        friend class Asset::World;
        friend class IdentityComponent;

        explicit EntityHandle();
        static EntityHandle Invalid();

        [[nodiscard]] bool GetIsValid() const { return IsValid; };
        [[nodiscard]] Entity GetEntity() const { return Entity; }
        [[nodiscard]] EntityID GetGUID() const { return GUID; }
        [[nodiscard]] uint64_t GetGUIDInt() const { return static_cast<std::uint64_t>(GUID); }

        bool operator==(const EntityHandle& handle) const;
        bool operator!=(const EntityHandle& handle) const;

    private:
        static EntityHandle Create(const EntityID guid, const Entity entity);


    private:
        bool IsValid;
        Entity Entity;
        EntityID GUID;
    };
}

namespace std {
    template<>
    struct std::hash<MeowEngine::Runtime::EntityHandle> {
        std::size_t operator()(const MeowEngine::Runtime::EntityHandle& handle) const noexcept {
            return std::hash<uint64_t>()(handle.GetGUIDInt());
        }
    };
}


#endif //MEOWENGINE_ENTITYHANDLE_HPP