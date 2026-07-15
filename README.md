# MeowEngine

C++ simulation engine for exploring engine architecture, multithreading, memory systems and computational physics.

---


<img src="screenshots/engine_v0.5.gif" alt="MeowEngine Banner">

---

## Overview

MeowEngine is a long-term personal engineering project focused on 
building a modern simulation engine in C++

Rather than targeting game development, the project serves as a 
platform for studying the engineering challenges behind 
large-scale simulation software. Each subsystem is designed to 
deepen my understanding of modern engine architecture while 
progressively moving towards computational physics research.

Rendering exists primarily as a tool for visualising and debugging simulations. 
The primary focus of the project is architecture, performance and physics.

---

## Long-Term Vision

The project is intentionally developed in stages, with each stage focusing on a different area of systems programming.

```
Engine Architecture
        ↓
Memory Systems & Profiling
        ↓
Multithreading
        ↓
Mathematics Library
        ↓
PhysX Integration
        ↓
Custom Physics Engine
        ↓
Physics Research Paper Simulations
```

The final objective is to create a platform capable of reproducing and experimenting with techniques described in academic physics and simulation research papers.

---

## Technology Stack

<table>
<tr>
<td valign="top">

| Category | Technology       | 
|-----------|------------------|
| Language | C++17            |
| Graphics | OpenGL           |
| Windowing | SDL              |
| Physics | NVIDIA PhysX     |
| Mathematics | GLM & Custom     |
| Build System | CMake            |
| Profiling | Tracy & Valgrind |

</td>

<td valign="top">

| Platform          | Support            |
|-------------------|--------------------|
| macOS x86_64      | :white_check_mark: |
| Mac (x84) Rosetta | :construction:     |
| Web               | :white_check_mark: |
| Window            | :soon:             |

</td>
</tr>
</table>

---

## Repository Structure

```
source/
├── core/
├── runtime/
├── graphics/
├── physics/
├── platform/
├── editor/
└── tools/
```

The architecture is intentionally modular to allow major
subsystems to evolve independently.

---

## Research

The final stage of the project is dedicated to implementing techniques from published physics
and simulation research papers.

The goal is to reproduce existing work, understand the underlying mathematics and use
MeowEngine as a platform for experimentation.

---

## Development Status

MeowEngine is an active long-term project.

Subsystems are frequently redesigned as new concepts are explored. Architectural 
refactoring is considered a normal part of development and is expected throughout 
the lifetime of the project.

- [Web demo](https://wulcat.com/meow-engine/index.html)
- [Version logs](markdowns/versions.md)
- [Screenshots](markdowns/Screenshots.md)

---

## Documentation
- [Build engine](markdowns/how_to_build.md)
- [Build documentation](markdowns/how_to_build.md)
- [See versions](markdowns/versions.md)
- [Learning resources](markdowns/references.md)