# 0009 — World and image coordinates

## Status

Proposed

## Context

Turning a pixel into a ray needs two ways of counting at once. An image is
stored and saved from its top-left corner, row by row, with rows going down.
The scene is described from the screen centre, with distances in world units.
Mixing the two up gives pictures that are upside down, mirrored or shifted
by half a pixel, and these bugs do not show on a centred, symmetric test.

## Decision

- **World:** x points right, y points up, z points forward, away from the eye.
  The camera looks along +z.
- **Image:** pixel (column, row) counts from the top-left corner; rows go down.
- **From pixel to world:** with pixel size s = screen width / image width,
  x = (column + 0.5 - width / 2) × s and y = (height / 2 - row - 0.5) × s.
  The 0.5 reaches the centre of the pixel and the minus sign flips y.
- Tests use odd, non-square images (for example 5 × 3) and off-centre pixels,
  so that a missing flip, a missing 0.5 or an integer division fails.

## Consequences

**Positive:**
- Images come out the right way up in every viewer, since PNG also starts at
  the top-left corner.
- The same convention as most ray tracing books, so examples can be compared.

**Negative:**
- Two systems to keep in mind; the y flip is easy to forget.
- A left-handed world (z forward) differs from the right-handed one used by
  some 3D tools, so imported scenes may need their z reversed.

**Rejected alternative:** counting image rows from the bottom, like the world's
y. It removes the flip in the camera, but every image would then have to be
flipped when saved, and the pixel index would no longer match the PNG layout.
