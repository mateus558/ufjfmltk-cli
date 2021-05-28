cmake_minimum_required(VERSION 3.19)
project(ufjfmltk-cli)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        ufjfmltk
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/mateus558/UFJF-Machine-Learning-Toolkit/archive/refs/tags/v0.50.0.tar.gz
)
FetchContent_MakeAvailable(ufjfmltk)

add_executable(cli main.cpp)
target_link_libraries(cli ufjfmltk)