# Domain model

The concepts of the ray tracer and how they relate, in the client's words.
Methods are left out on purpose, except the few that say who does what.

```mermaid
classDiagram
    class Vector {
        x
        y
        z
    }
    class Ray {
        origin
        direction
    }
    class Sphere {
        centre
        radius
    }
    class Camera {
        eye
        screenCentre
        screenWidth
        render(sphere, width, height) Image
    }
    class Image {
        width
        height
        pixel(column, row) Colour
    }
    class Colour {
        r
        g
        b
    }
    class Material {
        <<interface>>
        shade(ray) Colour
    }
    class FlatShader {
        colour
    }
    class ImageSaver {
        <<interface>>
        save(image, path)
    }
    class PngSaver

    Ray --> "2" Vector : origin, direction
    Sphere --> Vector : centre
    Sphere --> Material : material
    Material <|.. FlatShader
    FlatShader --> Colour : colour
    Camera --> "2" Vector : eye, screen centre
    Camera ..> Ray : one per pixel
    Camera ..> Image : renders
    Image --> "*" Colour : pixels
    ImageSaver <|.. PngSaver
    ImageSaver ..> Image : saves
```

## Decisions recorded so far

- **Is a colour a vector?** No, see [ADR 0007](../adr/0007-colour-is-its-own-class.md).
- **Are a point and a direction the same class?** For now yes: both are a `Vector`.
  Revisit if mixing them up causes bugs.
- **Who decides the colour of a pixel?** The free function `trace(ray, sphere)` in
  `src/render/trace.h` finds the hit; the sphere's `Material` gives the colour
  (`shade(ray)`); a miss is black. `FlatShader` gives one colour, whatever the ray.
- **Who makes the picture?** The camera renders the scene into an `Image`; it does not
  save itself: a saver saves it. `PngSaver` is the only saver today, behind the
  `ImageSaver` interface ([ADR 0008](../adr/0008-lodepng-for-png-output.md)).
- **How are pixels counted?** See [ADR 0009](../adr/0009-coordinates.md).

## Parked

- A `Sphere` refers to its material: the material must outlive the sphere. Passing a
  temporary material does not compile.
- `geometry/` and `material/` depend on each other (`Sphere` holds a `Material`, and
  `Material::shade` takes a `Ray`). Revisit when shading needs the hit point and normal.
- `Image` does not check pixel bounds: an out-of-range column or row is undefined behaviour.
- Colours outside 0..1 do not fit in a byte when saved.
- `render` takes one concrete `Sphere`.
- `main` does not catch the saver's exception.

## Folder dependencies

`render/` → `geometry/` → `math/`, `material/` → `colour/`, `render/` → `image/` ← `output/`.
One cycle, parked above: `geometry/` ↔ `material/`.
