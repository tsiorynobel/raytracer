# raytracer

A C++ ray tracer, built step by step with test-driven development.

The client's needs are in the [discovery report](docs/discovery/discovery-report.md).

## Getting started

The project runs in a dev container, so everyone has the same compiler and tools.

1. Install [Docker](https://www.docker.com/) and VS Code with the
   [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension.
2. Open this folder in VS Code and choose **Dev Containers: Reopen in Container**.
3. In the container terminal:

```bash
# Configure and build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

# Run
./build/raytracer
# Hello, Raytracer!

# Test
cd build && ctest --output-on-failure
```

Catch2 is downloaded at the first configure, so it needs internet access.
