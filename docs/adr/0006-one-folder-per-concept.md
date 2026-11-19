# 0006 — One folder per concept

## Status

Accepted

## Context

`src/` held `main.cpp` and the `Vector` files side by side. The domain model
already names more classes (Ray, Sphere, Camera, Image), and a flat folder
would soon mix unrelated files. We want a layout that grows with the project
and that tells a newcomer where a new class goes.

## Decision

- Each concept gets its own folder under `src/`, created with its first class
  (for example `src/math/` for `Vector`).
- Tests mirror `src/`: the tests of `src/math/vector.cpp` live in
  `tests/math/test_vector.cpp`.
- Includes start from `src/`, for example `#include "math/vector.h"`, so a
  file can move without breaking the includes of the files around it.
- Files are moved with `git mv` so their history is kept.

## Consequences

**Positive:**
- A class and its tests are easy to find.
- Include paths say which concept a file depends on.

**Negative:**
- More folders to create and to list in `CMakeLists.txt`.
- Moving a class to another concept means updating every include of it.

**Deliberately left out, and when to revisit:**
- Namespaces (`raytracer::Vector`): when names collide or partners embed the code.
- One CMake library per folder: when `math/` must not depend on `render/`, or
  build times grow.
- A separate `include/` folder: when we ship a library with public and private headers.
