https://web.archive.org/web/20060114082225/http://www.vision.ee.ethz.ch/~pmueller/documents/procedural_modeling_of_cities__siggraph2001.pdf
https://www.tmwhere.com/city_generation.html

📆 Milestones
1.	Project skeleton & CMake
2.	RoadGraph + L-system → live 2D roads
3.	Block extraction and debug overlays
4.	Footprint splitting
5.	Mesh extrusion & UVs
6.	OBJ export & Blender sanity-check
7.	glTF export & Godot round-trip
8.	Texture-atlas integration
9.	UI polish & presets
10.	Documentation, tests, sample scenes

# CityGen

A C++17 procedural city layout generator with SFML & ImGui, exporting to glTF 2.0 and OBJ for use in Blender, Godot 4, or other DCC tools.

---

## 🗺️ Features

- **L-System road network** with adjustable angle, depth, and density falloff
- **Block extraction** via planar graph left-hand walks
- **Building footprints** split by grid or straight-skeleton
- **3D mesh extrusion** with PBR UVs and texture atlas support
- **Exporters**: `.glb` (binary glTF 2.0) and `.obj` + `.mtl`
- Live **ImGui** panel for parameters, scene debug, and random seeds

---

## 🚀 Getting Started

### Prerequisites

- CMake ≥ 3.20
- A C++17-compatible compiler (Clang, GCC, MSVC)
- Git (to clone submodules)
- [SFML 3.0](https://www.sfml-dev.org/)
- [ImGui-SFML v3.1](https://github.com/eliasdaler/imgui-sfml)

### Build

```bash
git clone --recursive https://github.com/you/CityGen.git
cd CityGen
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -- -j$(nproc)
```
### Structure
```bash
CityGen/
├── CMakeLists.txt
├── README.md
├── extern/                     ← header-only libs as submodules
│   ├── earcut.hpp/             ← polygon triangulation
│   └── tinygltf/               ← glTF 2.0 read/write
├── assets/
│   └── textures/               ← your PBR atlases & mapping JSON
├── src/
│   ├── main.cpp                ← window + viewer glue
│   ├── Viewer/                 ← SFML & ImGui drawing code
│   │   └── CityViewer.hpp/.cpp
│   ├── City/                   ← core generation logic (framework-agnostic)
│   │   ├── RoadGraph.hpp/.cpp
│   │   ├── LSystemGenerator.hpp/.cpp
│   │   ├── BlockBuilder.hpp/.cpp
│   │   ├── FootprintSplitter.hpp/.cpp
│   │   └── ZoneAssigner.hpp/.cpp
│   ├── Mesh/                   ← mesh‐building utilities
│   │   └── MeshBuilder.hpp/.cpp
│   ├── Export/                 ← exporters for OBJ & glTF
│   │   ├── ObjExporter.hpp/.cpp
│   │   └── GltfExporter.hpp/.cpp
│   └── UI/                     ← ImGui panels & parameter structs
│       └── ParameterPanel.hpp/.cpp
├── tests/                      ← unit tests (e.g. Catch2)
│   └── test_RoadGraph.cpp
└── assets/                     ← textures & example output


