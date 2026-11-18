# 0008 — Write images as PNG with LodePNG

## Status

Proposed

## Context

The ray tracer must save what it renders so the client can look at it. The
course and the client both expect a picture file that any viewer can open.
Encoding PNG by hand (zlib compression, CRC checks, chunks) is a project of its
own and not what we are here to learn.

Alternatives considered:

- **PPM (plain text)** — trivial to write with no dependency, but many viewers
  cannot open it and the files are large.
- **stb_image_write** — one header, widely used, but a C API with raw pointers.
- **libpng** — the reference implementation, but a system library with a much
  larger API to learn and install.

## Decision

Use LodePNG, fetched with CMake `FetchContent` at a fixed commit
(`7b2893e35891c0c85bee5595caafaf3c2044b409`) and built as a small static library
`lodepng_lib`. Only `src/io/png_saver.cpp` includes it: the rest of the code
talks to the `ImageSaver` interface, so another format can be added without
touching the renderer.

## Consequences

**Positive:**
- Two source files, no system dependency, the same in the container and in CI.
- PNG opens everywhere: VS Code, browsers, image viewers.
- The `ImageSaver` interface keeps the file format out of the ray tracer.

**Negative:**
- The first configure needs internet access to download LodePNG.
- Pinned to one commit: updates are manual.
- One more third-party dependency to trust and to keep an eye on.
