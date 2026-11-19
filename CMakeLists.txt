cmake_minimum_required(VERSION 3.20)
project(raytracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# LodePNG
include(FetchContent)
FetchContent_Declare(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG        7b2893e35891c0c85bee5595caafaf3c2044b409
)
FetchContent_MakeAvailable(lodepng)
add_library(lodepng_lib STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
target_include_directories(lodepng_lib PUBLIC ${lodepng_SOURCE_DIR})

# Main executable
add_executable(raytracer src/main.cpp src/math/vector.cpp src/colour/colour.cpp src/geometry/ray.cpp src/geometry/sphere.cpp src/render/camera.cpp src/render/trace.cpp src/image/image.cpp src/io/png_saver.cpp)
target_include_directories(raytracer PRIVATE src)
target_link_libraries(raytracer PRIVATE lodepng_lib)

# Testing
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(tests tests/test_helpers.cpp tests/math/test_vector.cpp tests/colour/test_colour.cpp tests/geometry/test_ray.cpp tests/render/test_camera.cpp tests/geometry/test_sphere.cpp tests/render/test_trace.cpp tests/image/test_image.cpp tests/io/test_png_saver.cpp src/math/vector.cpp src/colour/colour.cpp src/geometry/ray.cpp src/geometry/sphere.cpp src/render/camera.cpp src/render/trace.cpp src/image/image.cpp src/io/png_saver.cpp)
target_include_directories(tests PRIVATE src tests)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain lodepng_lib)

include(CTest)
include(Catch)
catch_discover_tests(tests)
