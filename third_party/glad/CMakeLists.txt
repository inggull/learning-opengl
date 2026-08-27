project(
    glad
    LANGUAGES C
)

set(SRCS)

file(GLOB FILE_PATHS ${PROJECT_SOURCE_DIR}/src/*.c)
foreach(FILE_PATH ${FILE_PATHS})
    get_filename_component(FILE_NAME ${FILE_PATH} NAME)
    list(APPEND SRCS src/${FILE_NAME})
endforeach()

add_library(${PROJECT_NAME} STATIC ${SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)