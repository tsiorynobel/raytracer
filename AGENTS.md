# Agents

## Commands

Run every command inside the dev container.

**Build:**
```
make build
```

**Run:**
```
make run
```

**Test:**
```
make test
```

**Clean:**
```
make clean
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for dev container setup, make commands, TDD workflow, and how to work with ADRs.

See [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) for community standards.

## Architecture decisions

Our architecture decisions live in `docs/adr/`. Read them before changing the build system, tooling, or test setup.

## How we work

- **TDD:** write a failing test first, then only enough code to make it pass.
- Expected values come from the maths, not from running the code. If a test fails, ask before changing what it expects.
- One small step at a time — only what was asked for, nothing extra.
- Keep the C++ simple: no advanced features unless explicitly asked.
- Don't build or run anything on the host; all commands run inside the dev container.

## Structure

- New classes go in the folder matching their concept under `src/` (e.g. `src/math/`), and their tests in the matching folder under `tests/` (e.g. `tests/math/`).

## Style

- Private member variables must be prefixed with `_` (e.g. `_x`, `_name`).
- Do not use a `get` prefix on accessors — name them after the value they return (e.g. `x()`, not `getX()`).

## Rules

- Never go against an accepted ADR. To change a decision, write a new ADR with status `Proposed` and ask the user.
- Never set an ADR status to `Accepted`.
