# 0001 — Use a Dev Container

## Status

Proposed

## Context

Contributors join the project on Windows, macOS, and Linux, each with different
compiler versions and tool installations. Without a shared environment,
differences in GCC/Clang versions, CMake versions, or missing tools cause
"works on my machine" failures during the course.

Alternatives considered:

- **Native setup with documented prerequisites** — lower tooling overhead, but
  requires every participant to install and version-match GCC ≥ 12, CMake ≥ 3.20,
  and Git manually. Prone to drift and hard to debug during a live session.
- **CI-only standardisation** — catches integration problems but does not help
  during local development or live demos.

## Decision

Provide a `.devcontainer/devcontainer.json` backed by
`mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04`. VS Code and Zed open the
project inside this container automatically. The `postCreateCommand` configures
and builds the project on first launch, so participants arrive at a working
state without manual steps.

## Consequences

**Positive:**
- Every contributor uses the same compiler, CMake version, and Git, eliminating
  environment-related failures during the course.
- New contributors are productive within minutes of cloning the repository.

**Negative:**
- Requires Docker to be installed and running; Docker Desktop licencing may
  be a constraint for some participants.
- Container startup adds a one-time delay on first open.
- Participants who prefer a native workflow must configure their own toolchain
  to match the container's versions.
