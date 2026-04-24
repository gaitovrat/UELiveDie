# LiveDie

A short Unreal Engine 5.7 sandbox level. The player controls a character with
health, can pick up health packs to restore it, and can be killed by walking
into a kill trigger.

## Requirements

- Unreal Engine **5.7** (see `EngineAssociation` in `LiveDie.uproject`).
- Visual Studio 2022 with the **Game development with C++** workload
  (components listed in `.vsconfig`).
- [Git LFS](https://git-lfs.com/) — required; binary assets (`*.uasset`,
  `*.umap`, textures, audio, etc.) are stored via LFS.

## Getting started

```bash
git clone <repo-url>
cd LiveDie
git lfs install
git lfs pull
```

Then right-click `LiveDie.uproject` → **Generate Visual Studio project files**,
open `LiveDie.sln`, and build the **Development Editor** configuration. Launch
from Visual Studio or by double-clicking `LiveDie.uproject`.

## Development setup

The repo ships with [pre-commit](https://pre-commit.com/) hooks for whitespace,
line endings, large-file detection, and `clang-format` on C++ sources. After
cloning:

```bash
pre-commit install
```

Formatting is governed by `.clang-format` (Unreal conventions: hard tabs,
Allman braces, no column limit, `.generated.h` include order preserved).
