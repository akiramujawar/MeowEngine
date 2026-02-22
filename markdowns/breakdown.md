- Rewrite the sync logic -> 10
    - defining a structure
    - building the system for swap and sync
    - reworking the existing sync features entirely

- object selection
    - research
    - simple AABB / Sphere check
    - system for utility
    - bounding box creation
    - bounding volume hierarchy
    - mouse click and query
    - applying mouse click command
    - handling multiple selection

- maths & its implementation
    - vectors -> 2
    - quaternions -> 3
    - matrices -> 4
    - transforms -> 6
    - implementation -> 7
    - camera rework -> 8

 handles (requires maths & object selection & sync logic)
    - write shader for representations -> 1
    - selection & drag for the handles
    - calculating the commands to sync the handles
    - applying the sync to buffers

- creating file manager -> 12
    - What manes what?
        - System implies a processing loop
        - Manager implies ownership & cache

    - What goes where?
        - Anything runtime goes under engine/source
        - Anything editor goes under engine/source/editor
        - Any OS implementations goes under engine/source/platform
        - Anything platform specific variation goes under feature/platform
        - core is foundation - only pure c++
        - editor is tooling - uses features & core
        - engine is container which includes core,editor,other features
        - runtime is application

    - Flow
        - WorldLoader -> Some ResourceManager -> Some System -> Asset Manager -> File System

    - engine/source/core/file_system
        - namespace: MeowEngine::Core (core will have maths/ecs abstractions/memory allocators/logging/threading)
        - Path
        - FileSystem - exists/create/remove/copy/move/search/enumerate/read/write
        - FileData - only path, size, extension, other similar data
        - File - handling file streaming for large files required? a example given is file.open then file.read(buffer, 4096)
        - IFileWatcher

    - engine/source/core/stream
        - namespace: MeowEngine::Core
        - IStream

    - engine/source/platform/watcher
        - namespace: MeowEngine::Platform
        - WinFileWatcher, MacFileWatcher

    - engine/source/editor/watcher
        - namespace: MeowEngine::Editor
        - FileWatcherManager

    - engine/source/assets
        - namespace: MeowEngine::Asset
        - AssetManager - store the caches assets, async loading, manage reference counts
        - Asset - type, id etc.. (no file system relation)
        - AssetLoader - runtime to load them (heres where our custom formats go in .meowdata)
            - ObjectLoader, ImageLoader, ShaderLoader, SceneLoader etc...
        - AssetRegistry - contains the uuid to path relations, dependencies, all types of known asset types

    - engine/source/editor/assets
        - namespace: MeowEngine::Editor
        - AssetThumbnail (this contain a png format thumnail for editor usage only)
        - AssetImporter - only import engine png format, engine fbx format etc... (not to read and conver into engine object formats) (mostly we dont need as we dont have custom types to import)

    - engine/source/graphics
        - namespace: MeowEngine::Graphics
        - IGraphicsDevice (GPUBuffer, GPUTexture, ShaderModule, Pipeline)

    - engine/source/runtime/rendering
        - namespace: MeowEngine::Runtime
        - IRenderSystem  (CreateMesh, CreateTexture, CreateShader)

    - engine/source/runtime/resource
        - namespace: MeowEngine::Runtime
        - RenderResourceManager - calls AssetManager.load & IRenderSystem.create & cache
        - AudioResourceManager - calls AssetManager.load & IAudioSystem.create & cache
        - PhysicsResourceManager - calls AssetManager.load & IPhysicsSystem.create & cache
        - StreamManager

    - engine/source/runtime/world
        - namespace: MeowEngine::Runtime
        - WorldLoader
        - World

    - engine/source/editor/selector
        - namespace MeowEngine::Selection
        - WorldTreeSelector - selecting the entities from WorldTree or WorldView windows
        - AssetSelector - selecting assets from Assets window

    - engine/source/serialization
        - namespace: MeowEngine::Serialization - should operate on stream
        - Serialize
        - Deserialize

    - engine/source/packaging
        - namespace: MeowEngine::Package
        - BuildSystem
        - BuildSetting

    - engine/source/packaging/platform
        - namespace: MeowEngine::Package
        - MacBuildSetting
        - WinBuildSetting

    - namespace: MeowEngine::Platform
        - engine/source/platform
        - (any native platform specific extender which is part of engine comes here)
        - (native dialogs, os timing, platform detection)
        - PlatformType

- learning / understanding / implementing tracy thoroughly -> 13

- documenting every system for deeper understanding -> 11

- creating alternate systems for switching maths/ physics/ rendering

- hierarchy for objects -> 9
    - hierarchy component defines the tree
    - may or may not require transforms i.e. any entity with hierarchy component can be a child of a entity component
    - create separate vector of transforms in topology format
        - this will help us recompute child transforms in elegant way
        - the only question would be will the topology will be a large data structure storing all transforms from world or isolated within each root node of entity

    - engine/source/components
        - namespace: MeowEngine::Component
        - TreeComponent
        - InfoComponent
        - TransformComponent etc...

    - engine/source/runtime/transform
        - namespace: MeowEngine::Runtime
        - TransformSystem - stores topology order vector of entt::entity. It gets the transform component to calculate the recompute

    - ECS Layer - handled by entt (won't be present inside source, if extensions they go under core/ecs)
        - EnTT (AoS sparse-set)
        - Entity metadata
        - Handles to systems

    - engine/source/runtime/physics
        - namespace: MeowEngine::Runtime
        - PhysicsSystem

    - engine/source/physics
        - namespace: MeowEngine::Physics
        - SoA storage
        - Broad phase
        - Constraint graph
        - Island detection
        - Solver
        - Parallel jobs

    - engine/source/runtime/synchronization
        - Double buffering
        - Stable handles
        - FrameSync

- ui logger
    - requires file manager

- builds
    - build for mac
    - build for windows
    - optimising build process