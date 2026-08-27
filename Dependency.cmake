include(FetchContent)

add_subdirectory(glad)
add_subdirectory(imgui)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.x
    GIT_SHALLOW 1
)

FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW 1
)

FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
    GIT_SHALLOW 1
)

FetchContent_MakeAvailable(glm)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(glad PUBLIC /utf-8)
    target_compile_options(spdlog PUBLIC /utf-8)
    target_compile_options(glfw PUBLIC /utf-8)
    target_compile_options(glm PUBLIC /utf-8)
endif()

list(APPEND LIBS glad spdlog glfw glm imgui)