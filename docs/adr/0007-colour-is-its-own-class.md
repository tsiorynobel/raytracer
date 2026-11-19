# 0007 — Colour is its own class, not a Vector

## Status

Accepted

## Context

A colour is three numbers (r, g, b), like a vector (x, y, z). Reusing `Vector`
for colours would give us addition and scaling for free. The pinhole spike had
to decide, because a `Sphere` needs a colour and `trace` returns one.

The two concepts behave differently:

- Colours mix (multiply component by component), are clamped to 0..1 and are
  converted to 0..255 when written to an image.
- Vectors have a dot product, a length and can be normalised, which make no
  sense for a colour.

## Decision

`Colour` is its own class in `src/colour/`, with three private doubles `_r`,
`_g`, `_b` and the accessors `r()`, `g()`, `b()`. It gets new operations only
when a test needs them.

## Consequences

**Positive:**
- The type says what a value means: a function that takes a `Colour` cannot be
  given a direction by mistake.
- Colour-only operations (mixing, clamping, 0..255) have an obvious home.
- `colour/` depends on nothing, so `geometry/` and `render/` can use it without
  a cycle.

**Negative:**
- Some code looks duplicated between `Vector` and `Colour` (three components,
  similar constructors).
- Operations shared by both, such as scaling, must be written twice.

**Rejected alternative:** Colour as a `Vector` (or a type alias of it). Simpler
today, but it would allow `colour.normalised()` or `colour.dot(direction)`, and
it would mix two concepts the client keeps apart.
