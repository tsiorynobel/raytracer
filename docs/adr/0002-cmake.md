# 0002 — Use CMake (with CTest)

## Status

Accepted

## Context

The project must build on Windows, macOS, and Linux, and needs to integrate
with VS Code (CMake Tools extension), Zed, and plain terminal workflows. It
also needs to fetch Catch2 at configure time without requiring a separate
package manager.

Alternatives considered:

- **Make / GNU Make** — simple, but not natively cross-platform (requires
  MinGW or WSL on Windows) and lacks IDE integration.
- **Meson** — modern and fast, but less familiar to most C++ developers and
  less well-supported by common IDE extensions.
- **Bazel** — powerful for large monorepos, but heavy overhead for a small
  course project; steep learning curve.

## Decision

Use CMake (minimum version 3.20) as the build system, with CTest for running
tests. `FetchContent` pulls Catch2 v3 at configure time, eliminating the need
for a package manager. `catch_discover_tests` registers each `TEST_CASE` with
CTest automatically.

## Consequences

**Positive:**
- Works on all target platforms and integrates with VS Code (CMake Tools),
  CLion, Zed, and the terminal without extra configuration.
- `FetchContent` keeps the repository self-contained: no external package
  manager or vendored copies needed.
- CTest provides a uniform `ctest` invocation regardless of the test framework
  used.

**Negative:**
- CMake's syntax is verbose and historically inconsistent; the learning curve
  can be steep for participants unfamiliar with it.
- `FetchContent` downloads Catch2 on first configure, which requires internet
  access and adds a noticeable delay.
- Minimum version 3.20 may not be pre-installed on older Linux distributions.
