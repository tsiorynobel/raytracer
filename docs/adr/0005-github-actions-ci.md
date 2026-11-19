# 0005 — Use GitHub Actions for CI

## Status

Accepted

## Context

Pull requests need automated verification that the project builds and all
tests pass before merging. Without CI, broken changes can land undetected and
contributors receive no feedback until a maintainer reviews manually.

The project already uses a dev container
([ADR 0001](0001-dev-container.md)) backed by
`mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04`. CI should use the same
environment to avoid "passes locally, fails in CI" problems.

Alternatives considered:

- **CircleCI** — mature, but requires a separate account and configuration
  file format. Less native to GitHub-hosted repositories.
- **Travis CI** — historically popular for open source, but its free tier for
  public repositories has become significantly restricted.
- **Self-hosted runner** — full control over the environment, but requires
  maintaining infrastructure and is disproportionate for a small project.

## Decision

Use GitHub Actions with a workflow that:

1. Triggers on every pull request and every push to `main`.
2. Runs inside the same container image as the dev container
   (`mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04`) to match the local
   environment exactly.
3. Executes `make build` followed by `make test`.
4. Reports pass/fail status back to the pull request so it cannot be merged
   until both steps succeed.

## Consequences

**Positive:**
- CI runs in the same container image as local development, eliminating
  environment drift between local and CI.
- GitHub Actions is free for public repositories and requires no additional
  account or service.
- Native integration with GitHub pull requests: status checks block merges
  automatically.

**Negative:**
- Ties CI to GitHub; migrating to a different host would require rewriting the
  workflow.
- Container image startup adds time to each CI run compared with a bare runner.
- `FetchContent` downloads Catch2 on first configure; caching the CMake build
  directory between runs would be needed to keep CI fast as the project grows.
