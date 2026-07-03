## Plan of action
[...previous plan of actions](previous_plan_of_actions.md)

## Meow Engine v0.5
- [ ] Reimplementing physics with new architecture for multithreaded synchronisation
- [x] Populating enums, pointers classes in edit panel
- [x] Automated component registration in triple buffer
- [x] Adding Rotations & Scaling to transform & physics bodies
- [x] Adding navigation to github / go back for web builds
- [x] Build a new architecture for multithreading (using Scheduler)
- [x] Position, Scale, Rotation handles for selected objects
- [x] Extending Property Reflections to support dynamic method calls - this will for euler to quat
- [x] File Manager (show directories, files, rename, move & delete & import)
- [x] Simple tool for importing files like textures/meshes
- [x] Create Unique ID generator for items
- [x] Hierarchy for entities
- [x] Reworking asset loading pipeline
- [x] Ability to read/write on file for saving import references (instead of hard-coded enums)
- [x] Creating support for multi-scene compilation
- [x] Improving current shader pipeline to handle shaders dynamically
- [ ] Render loading pipeline (shaders, textures, meshes)
- [x] Reworking camera system to use quaternion
- [x] Messaging systems (command, request & event)
- [x] Config load & bootstrap for editor load
- [x] Refactor cmake to have engine & standalone lib
- [x] Find a way to isolate and build code while developing simulations
- [x] Dynamic shader rebuild
- [x] Play & Pause & Stop

## Meow Engine v0.6
- [ ] Creating library for performing basic mathematical operations for vectors & quaternion & matrix
- [ ] Implement Tracy throughout engine for performance profiling
- [ ] For memory error detector: valgrind / address sanitizer
- [ ] Implement job system for multithreading
- [ ] Add Unit Testing
- [ ] Asset Directory needs to updated after actions (create/delete/move/rename)
- [ ] Asset Database needs to be updated after actions (create/delete/move/rename)
- [ ] Documenting done items and different approaches and used libraries

## Meow Engine v0.7
- [ ] Hierarchy and transforms + ui drag n drop for hierarchy
- [ ] Runtime handles -> to store different viewports / frame buffers
- [ ] Reworking engine to utilise new mathematical library
- [ ] Decoupling SDL events with the help of messaging system
- [ ] Selecting objects in scene renderer (world) using GPU & guid
- [x] Compilation of physx for web
- [x] Single thread app builds for web
- [ ] Populating arrays / lists etc... in WorldInspectorPanel
- [ ] Updating bash files for supporting physx on mac
- [ ] Support for window
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