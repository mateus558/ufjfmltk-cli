# Install script for directory: C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-clusterer

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/ufjfmltk-cli")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ufjfmltk/clusterer" TYPE FILE FILES
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-clusterer/include/ufjfmltk/clusterer/Clusterer.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-clusterer/include/ufjfmltk/clusterer/KMeans.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ufjfmltk" TYPE FILE FILES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-clusterer/include/ufjfmltk/Clusterer.hpp")
endif()

