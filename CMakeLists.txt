cmake_minimum_required(VERSION 3.19)
project(ufjfmltk-cli)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(ufjfmltk)
add_subdirectory(cppcli)
add_subdirectory(widgets)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} widgets)