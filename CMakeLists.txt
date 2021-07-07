cmake_minimum_required(VERSION 3.15)
project(ufjfmltk-cli
        LANGUAGES CXX C
        VERSION 1.0.2)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
FetchContent_Declare(
        ufjfmltk
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/mateus558/UFJF-Machine-Learning-Toolkit/archive/refs/tags/v0.51.1-beta.9.tar.gz
)
FetchContent_MakeAvailable(ufjfmltk)

FetchContent_Declare(
        cppcli
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/mateus558/cppcli/archive/refs/tags/v1.2.1.tar.gz
)
FetchContent_MakeAvailable(cppcli)

#add_subdirectory(ufjfmltk)
#add_subdirectory(cppcli)
add_subdirectory(widgets)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} widgets)

install(TARGETS ${PROJECT_NAME}
        EXPORT  ${PROJECT_NAME}
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" COMPONENT dev)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_subdirectory(packaging) # include(CPack) will happen in here
endif()
