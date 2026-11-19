# 0004 — Short commands with a Makefile

## Status

Accepted

## Context

Building, running and testing need several CMake and CTest commands with
options that are easy to mistype (`cmake -S . -B build`, `cmake --build build`,
`cd build && ctest --output-on-failure`). Newcomers, AI assistants and CI should
all run exactly the same steps, the way `npm run build` or `npm test` work in a
JavaScript project.

Alternatives considered:

- **CMake presets only** — standard and cross-platform, but the commands stay
  long (`cmake --workflow --preset ...`) and are hard to remember.
- **Shell scripts** (`build.sh`, `test.sh`) — simple, but one file per command
  and no dependency between steps.
- **A task runner** (`just`, `task`) — nicer syntax, but one more tool to
  install in the container and on every machine.

## Decision

Add a `Makefile` at the root with four targets that wrap CMake and CTest:

- `make build` — configure and compile.
- `make run` — build, then run the program.
- `make test` — build, then run the tests.
- `make clean` — delete the `build/` folder.

`run` and `test` depend on `build`, so they always use up-to-date binaries.

## Consequences

**Positive:**
- One short command per task, the same for people, AI assistants and CI.
- GNU Make is already in the dev container image.

**Negative:**
- Make is not available by default on Windows outside the container.
- Recipe lines must be indented with tabs; spaces, or Windows line endings,
  break the file with `missing separator`.
- The targets hide the CMake commands, so a newcomer may not learn them.
