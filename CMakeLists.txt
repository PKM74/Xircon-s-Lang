cmake_minimum_required(VERSION 3.25.0)
project(xic)

set(CMAKE_CXX_STANDARD 26)

add_executable(${PROJECT_NAME} src/main.cxx)

target_link_libraries(
    ${PROJECT_NAME}
)