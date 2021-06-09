# Install script for directory: C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/Debug/cored.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/Release/core.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/MinSizeRel/core.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/RelWithDebInfo/core.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ufjfmltk/core" TYPE FILE FILES
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/Data.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/Datasets.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/Point.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/DistanceMetric.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/Kernel.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/Learner.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/Point.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/Random.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/Sampling.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/Solution.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/Statistics.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/Timer.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/Utils.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/ExprOps.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/ExprScalar.hpp"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/core/ExprTraits.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ufjfmltk" TYPE FILE FILES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include/ufjfmltk/Core.hpp")
endif()

