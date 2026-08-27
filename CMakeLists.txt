cmake_minimum_required(VERSION 3.11)

project(
    learning-opengl
    LANGUAGES C CXX
    VERSION 0.1.0
    HOMEPAGE_URL https://github.com/inggull/learning-opengl
    DESCRIPTION ""
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(LIBS)

include(Dependency.cmake)
add_subdirectory(01_hello_window)
add_subdirectory(02_shader)
add_subdirectory(03_program)
add_subdirectory(04_context)
add_subdirectory(05_hello_triangle)
add_subdirectory(06_buffer)
add_subdirectory(07_texture)
add_subdirectory(08_transformation)
add_subdirectory(09_camera)
add_subdirectory(10_interactive_camera)
add_subdirectory(11_imgui)