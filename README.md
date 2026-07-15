# MeowEngine

A research driven C++ simulation engine for exploring engine architecture, multithreading, 
memory and computational physics.

---

<img src="screenshots/engine_v0.5.gif" alt="MeowEngine Banner">

---

## Overview

This project serves as a platform for studying the engineering challenges 
behind 3D engine. Each subsystem is designed to 
deepen my understanding of modern engine architecture while 
progressively moving towards computational physics research.

Rendering exists primarily as a tool for visualising and debugging simulations. 
The primary focus of the project is architecture, performance and physics.

---

## Long-Term Vision

The project is intentionally developed in stages, with each stage 
focusing on a different area of programming.

```
Engine Architecture
        ↓
PhysX Integration
        ↓
Multithreading
        ↓
Memory Systems & Profiling
        ↓
Custom Mathematics Library       
        ↓
Custom Physics
        ↓
Physics Research Paper Simulations
```

The final objective is to create a platform capable of 
reproducing and experimenting with techniques described in academic physics and simulation research papers.

---

## Technology Stack
| Category      | Value             | - | Platform      | Status |
|---------------|-------------------|---|----------------| ------ |
| Language      | C++17             | - | macOS x86_64 | ✅      |
| Graphics      | OpenGL            | - | macOS (Rosetta) | 🚧     |
| Physics       | NVIDIA PhysX      | - | Web     | ✅      |
| Mathematics   | GLM & Custom      | - | Windows | 🔜     |
| Build         | CMake             | - |        |
| Profiling     | Tracy & Valgrind  | - |        |

---

## Repository Structure

- **Core** – Mathematics, memory management, utilities, threading, io
- **Platform** – Windowing, platform abstraction.
- **Graphics** – Graphics API abstraction, buffers, shaders and GPU resources.
- **Rendering** – Renderer, pipeline, passes
- **Runtime** – Asset management, project, gameplay, world, reflection
- **Editor** – Tools, profilers, editor panels.
- **Physics** – PhysX integration and plans to custom physics

The architecture is intentionally modular to allow major
subsystems to evolve independently.

---

## Development Status

MeowEngine is an active long-term project.

Subsystems are frequently redesigned as new concepts are explored. Architectural 
refactoring is considered a normal part of development and is expected throughout 
the lifetime of the project.

- [Web demo](https://wulcat.com/meow-engine/index.html)
- [Version logs](markdowns/versions.md)
- [Screenshots](markdowns/Screenshots.md)
- [Next plan of action...](markdowns/plan_of_action.md)

---

## Documentation
- [Build engine](markdowns/how_to_build.md)
- [Build documentation](markdowns/how_to_build.md)
- [See versions](markdowns/versions.md)
- [Learning resources](markdowns/references.md)

---

## Screenshots
<table>
    <tr>
        <td align="center" width="50%">
            <img width="320" src="screenshots/engine_v0.5.gif" alt="Engine">
        </td>
        <td align="center" width="50%">
            <img width="320" src="screenshots/engine_profiling.png" alt="Profiler">
        </td>
    </tr>
    <tr>
        <td align="center" width="33%">
            MeowEngine v0.5
        </td>
        <td align="center" width="33%">
            Tracy Frame Profiling 
        </td>
    </tr>
</table>