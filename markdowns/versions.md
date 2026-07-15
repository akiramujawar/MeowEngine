## Releases

### [v0.5 (gif)](../screenshots/engine_v0.5.gif)
- Reimplementing physics with new architecture for multithreaded synchronisation
- Populating enums, pointers classes in edit panel
- Automated component registration in triple buffer
- Adding Rotations & Scaling to transform & physics bodies
- Adding navigation to github / go back for web builds
- Build a new architecture for multithreading (using Scheduler)
- Position, Scale, Rotation handles for selected objects
- Extending Property Reflections to support dynamic method calls - this will for euler to quat
- File Manager (show directories, files, rename, move & delete & import)
- Simple tool for importing files like textures/meshes
- Create Unique ID generator for items
- Hierarchy for entities
- Reworking asset loading pipeline
- Ability to read/write on file for saving import references (instead of hard-coded enums)
- Creating support for multi-scene compilation
- Improving current shader pipeline to handle shaders dynamically
- Render loading pipeline (shaders, textures, meshes)
- Reworking camera system to use quaternion
- Messaging systems (command, request & event)
- Config load & bootstrap for editor load
- Refactor cmake to have engine & standalone lib
- Find a way to isolate and build code while developing simulations
- Dynamic shader rebuild
- Play & Pause & Stop

### [v0.4 (gif)](../screenshots/engine_v0.4.gif)
  - Engine supports multithreading splitting into main, render and physics threads
  - Added PhysX for simulating physics
  - Added Reflections to display and edit components properties dynamically through UI
  - Runtime method to create life objects
  - Removed support for Web due to multithreading & PhysX compatibility
### [v0.3 (gif)](../screenshots/engine_v0.3.gif)
  - UI using Dear ImGui
  - Frame Buffer for rendering scene into window panel
  - Keyboard and Mouse Input Handling
  - Free camera movement
  - Entity component system
### [v0.2 (gif)](../screenshots/engine_v0.2.gif)
  - Basic rotations and positioning for objects
  - Reads texture and applies to mesh
  - Keyboard & Mouse Inputs
### [v0.1 (screenshot)](../screenshots/engine_v0.1.png)
  - Creates application using SDL & OpenGL
  - Reads files (obj & vert, frag shaders)
  - Mesh rendering with camera projection
