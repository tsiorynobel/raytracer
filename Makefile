.PHONY: build run test clean

build:
	cmake -S . -B build
	cmake --build build

run: build
	./build/raytracer

test: build
	cd build && ctest --output-on-failure

clean:
	rm -rf build
