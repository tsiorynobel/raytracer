# raytracer

[![CI](https://github.com/tsiorynobel/raytracer/actions/workflows/ci.yml/badge.svg)](https://github.com/tsiorynobel/raytracer/actions/workflows/ci.yml)

A C++ ray tracer, built step by step with test-driven development.

Licence: [MIT](LICENSE) · [Contributing](CONTRIBUTING.md) · [Code of Conduct](CODE_OF_CONDUCT.md) ·
[Architecture decisions](docs/adr/)

The client's needs are in the [discovery report](docs/discovery/discovery-report.md).

## Getting started

The project runs in a dev container, so everyone has the same compiler and tools.

1. Install [Docker](https://www.docker.com/) and VS Code with the
   [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension.
2. Open this folder in VS Code and choose **Dev Containers: Reopen in Container**.
3. In the container terminal:

| Command | What it does |
|---------|-------------|
| `make build` | Configure and compile everything |
| `make run` | Build, then run the ray tracer |
| `make test` | Build, then run the tests |
| `make clean` | Delete the `build/` folder |

```bash
make run
# image.png
```

The program traces one ray per pixel from a pinhole camera at (0, 0, -1) towards a red
sphere and saves a 400 x 300 picture as `image.png` in the project folder (not committed).

## Documentation

- [Domain model](docs/domain/domain-model.md)
- [Architecture decisions](docs/adr/)
- [Pinhole spike notes](docs/spikes/pinhole-spike.md)

See [ADR 0004](docs/adr/0004-makefile.md) for why we use a Makefile.

Catch2 is downloaded at the first configure, so it needs internet access.
