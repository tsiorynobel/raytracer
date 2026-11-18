# Agents

## Commands

Run every command inside the dev container.

**Build:**
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

**Run:**
```
./build/raytracer
```

**Test:**
```
cd build && ctest --output-on-failure
```

## Architecture decisions

Our architecture decisions live in `docs/adr/`. Read them before changing the build system, tooling, or test setup.

## Rules

- Never go against an accepted ADR. To change a decision, write a new ADR with status `Proposed` and ask the user.
- Never set an ADR status to `Accepted`.
