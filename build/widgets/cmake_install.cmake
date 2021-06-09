# Install script for directory: C:/Users/Marim/source/repos/ufjfmltk-cli/widgets

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/Marim/source/repos/ufjfmltk-cli/build/widgets/factory/cmake_install.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/widgets/Debug/widgets.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/widgets/Release/widgets.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/widgets/MinSizeRel/widgets.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/widgets/RelWithDebInfo/widgets.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "C:/Users/Marim/source/repos/ufjfmltk-cli/widgets/include/ArtificialDataWidget.h"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/widgets/include/DatasetWidget.h"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/widgets/include/DataWidget.h"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/widgets/include/ClassifiersWidget.h"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/widgets/include/RegressorWidget.h"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/widgets/include/FeatSelectWidget.h"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/widgets/include/VisualizationWidget.h"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/widgets/include/ClustererWidget.h"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/widgets/include/ValidationWidget.h"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/widgets/include/MLTKApp.h"
    "C:/Users/Marim/source/repos/ufjfmltk-cli/widgets/include/settings.h"
    )
endif()

