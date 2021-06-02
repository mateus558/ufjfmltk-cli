cmake_minimum_required(VERSION 3.19)
project(ufjfmltk-cli)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
FetchContent_Declare(
        ufjfmltk
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/mateus558/UFJF-Machine-Learning-Toolkit/archive/refs/tags/v0.51.0.tar.gz
)
FetchContent_MakeAvailable(ufjfmltk)

include(FetchContent)
FetchContent_Declare(
        cppcli
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/mateus558/cppcli/archive/refs/tags/v1.1.0.tar.gz
)
FetchContent_MakeAvailable(cppcli)

#add_subdirectory(ufjfmltk)
#add_subdirectory(cppcli)
add_subdirectory(widgets)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} widgets)