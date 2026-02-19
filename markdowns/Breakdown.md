### Rewrite the sync logic -> 10
- defining a structure
- building the system for swap and sync
- reworking the existing sync features entirely
### object selection
  - research
  - simple AABB / Sphere check
  - system for utility
  - bounding box creation
  - bounding volume hierarchy
  - mouse click and query
  - applying mouse click command
  - handling multiple selection
### maths & its implementation
  - vectors -> 2
  - quaternions -> 3
  - matrices -> 4
  - transforms -> 6
  - implementation -> 7
  - camera rework -> 8
### handles (requires maths & object selection & sync logic)
  - write shader for representations -> 1
  - selection & drag for the handles
  - calculating the commands to sync the handles
  - applying the sync to buffers
### creating file manager -> 12
### learning / understanding / implementing tracy thoroughly -> 13
### documenting every system for deeper understanding -> 11
### creating alternate systems for switching maths/ physics/ rendering
### hierarchy for objects -> 9
- requires transforms
### ui logger
- requires file manager
  builds
- build for mac
- build for windows
- optimising build process