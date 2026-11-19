# 0010 — A shape has a material

## Status

Accepted

## Context

The scene now holds two shapes, a sphere and a plane, and the ball and the floor
must look different. How a surface takes light (flat, matte, and later a mirror or
glass) is a different question from where a ray meets it (a sphere, a plane, and
later a cylinder). If each answer is tied to the other, every new shape or new look
multiplies the code.

## Decision

- **Composition:** a shape *has* a material. `Sphere` and `Plane` hold a
  `const Material&` and put it in the `Hit` they return; `trace` asks that material
  for the colour. The shape decides where, the material decides how it looks.
- **Strategy:** `Material` is an interface with one method,
  `shade(normal, toLight)`, where both vectors are unit vectors. Each way of shading
  is its own class: `FlatShader` (one colour) and `LambertShader`
  (max(0, N . L) × colour). A new look is a new class; no shape changes.
- **Ownership:** a shape refers to its material, it does not own it. The material
  must outlive the shape; passing a temporary does not compile.

## Consequences

**Positive:**
- Shapes and materials grow side by side: n shapes + m materials classes, not n × m.
- Open for extension: a new shape or a new material is a new class, plus its line in
  `CMakeLists.txt` and its use in `main`.
- `material/` does not depend on `geometry/`, since `shade` takes vectors, not a hit.

**Negative:**
- A virtual call per shaded pixel.
- The caller must keep the materials alive as long as the scene (in `main`, they are
  declared before it).
- Each shape repeats the same material member and constructor plumbing.

**Rejected alternatives:**
- *Inheritance:* `RedSphere`, `MatteSphere`, `MattePlane`... one class per shape and
  look, and the same lighting code copied into each.
- *One concrete `Material` class holding a colour, with Lambert built in (the course's
  version):* simpler today, but a mirror or a flat colour would mean changing that
  class and every place that uses it, instead of adding one.
