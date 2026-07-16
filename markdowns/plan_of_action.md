## Plan of action

[...previous plan of actions](previous_plan_of_actions.md)

## Meow Engine v0.5
- [ ] Proper plane setup
- [ ] Cannot deserialize after deleting component
- [ ] Check if removing component is okay for deserialization
- [ ] Transparency from grid
- [ ] Play/Pause buttons
- [ ] Renaming files and retaining extensions
- [ ] Asset Directory extraction
- [ ] Decoupling rendering from runtime & editor
- [ ] Splitting & renaming existing systems for reflections
- [ ] Adding menu item for asset directory rebuild & auto rebuild on actions
- [ ] Mesh Collider?
- [ ] Decoupling asset handles , entity handles etc...
- [ ] Names on handle references

## Meow Engine v0.6
- [ ] Creating library for performing basic mathematical operations for vectors & quaternion & matrix
- [ ] Implement Tracy throughout engine for performance profiling
- [ ] For memory error detector: valgrind / address sanitizer
- [ ] Implement job system for multithreading
- [ ] Add Unit Testing
- [ ] Documenting done items and different approaches and used libraries
- [ ] Transforms Hierarchy (local + global positions / rotations / scales)
- [ ] Collider Rendering
- [ ] Support for window

## Meow Engine v0.7
- [ ] Reflection for engine assets
- [ ] Creating separate libs in cmake for editor, runtime, rendering & physics
- [ ] Run through all engine handles like EntityID, ComponentID, ComponentHash etc...
- [ ] Hierarchy and transforms + ui drag n drop for hierarchy & reordering
- [ ] Runtime handles -> to store different viewports / frame buffers
- [ ] Reworking engine to utilise new mathematical library
- [ ] Decoupling SDL events with the help of messaging system
- [ ] Selecting objects in scene renderer (world) using GPU & guid
- [x] Compilation of physx for web
- [x] Single thread app builds for web
- [ ] Populating arrays / lists etc... in WorldInspectorPanel
- [ ] Updating bash files for supporting physx on mac
- [ ] Research on making dev/debug builds for in-depth testing
- [ ] Creating vehicle using PhysX
- [ ] Creating wrapper for switching between different physics engine
- [ ] If simple, add basic light and sky box
- [ ] Researching on auto-build deployment and build status
- [ ] Create build modes for debug and release
- [ ] 2 builds for web - engine & a multi-scene simulation
- [ ] Create a template for dump-testing shaders
- [ ] Dynamic Window Layout & save'n'load
- [ ] Setting up Vulkan
- [ ] Creating 3D spatial hashing (showcase & in-built)
- [ ] Updating pipeline to use HLSL
- [ ] Refactor to utilise <system/file.hpp> instead of "file.hpp" (include changes)
- [ ] Create a client which will cache engine directory & can create sandboxes & cache them as well. 