cmake_minimum_required(VERSION 3.14.0)
project(xic
    LANGUAGES C
        DESCRIPTION "XILANG Compilier"
)

set(CVERSION "-std=c99")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CVERSION}")

add_executable(${PROJECT_NAME} src/main.c)

target_link_libraries(
    ${PROJECT_NAME}
)