project(
    imgui
    LANGUAGES CXX
)

set(SRCS)

file(GLOB FILE_PATHS ${PROJECT_SOURCE_DIR}/src/*.cpp)
foreach(FILE_PATH ${FILE_PATHS})
    get_filename_component(FILE_NAME ${FILE_PATH} NAME)
    list(APPEND SRCS src/${FILE_NAME})
endforeach()

add_library(${PROJECT_NAME} STATIC ${SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw)