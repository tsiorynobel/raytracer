# Contributing

Thank you for your interest in contributing to this project.

## Code of conduct

Please read [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) before participating.

---

## Setting up your development environment

### Option A — Dev container (recommended)

Requires [Docker](https://www.docker.com/) and either VS Code with the
[Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)
extension, or Zed with its built-in dev container support.

1. Clone the repository.
2. Open the folder in VS Code or Zed.
3. When prompted, click **"Reopen in Container"** (VS Code) or **"Use Dev
   Container"** (Zed).
4. The container provides GCC, CMake ≥ 3.20, and Git. CMake configures and
   builds automatically on first launch via `postCreateCommand`.

This is the approach described in [ADR 0001](docs/adr/0001-dev-container.md)
and is the environment used by CI.

### Option B — Native

| Tool | Minimum version |
|------|----------------|
| CMake | 3.20 |
| C++ compiler | GCC 12 / Clang 15 / MSVC 19.34 (C++20) |
| Git | any recent |

---

## Make commands

| Command | What it does |
|---------|-------------|
| `make build` | Configure + compile everything |
| `make run` | Build then launch the raytracer |
| `make test` | Build then run the test suite |
| `make clean` | Delete the `build/` directory |

`run` and `test` both trigger a build, so sources are always recompiled if
they have changed.

---

## Test-driven development workflow

This project follows TDD. Every change should start with a failing test.

1. Write a `TEST_CASE` in `tests/` that describes the behaviour you want.
2. Run `make test` and confirm the new test fails.
3. Implement the minimum code to make it pass.
4. Run `make test` again and confirm all tests pass.
5. Refactor if needed, keeping the tests green throughout.

Do not submit a pull request whose tests do not pass (`make test` must
succeed cleanly).

---

## Architecture decision records

Significant decisions about build tooling, testing frameworks, and project
structure are recorded in [`docs/adr/`](docs/adr/).

Before changing the build system, tooling, or test setup:

1. Read the existing ADRs to understand what was decided and why.
2. Never act against an accepted ADR.
3. If you believe a different approach is better, write a new ADR with status
   `Proposed` and open a discussion issue before making any changes.
4. Do not set an ADR's status to `Accepted` yourself — that is the
   maintainer's decision.

---

## Submitting a pull request

1. Fork the repository and create a branch from `main`.
2. Make your changes following the TDD workflow above.
3. Run `make test` and confirm all tests pass.
4. Open a pull request against `main`. The PR template will prompt you for
   the information needed.
5. CI will run `make build` and `make test` automatically. The PR cannot be
   merged until both pass.
