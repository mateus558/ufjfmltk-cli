# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6...3.18)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

if(CMAKE_VERSION VERSION_LESS 3.0.0)
  message(FATAL_ERROR "This file relies on consumers using CMake 3.0.0 or greater.")
endif()

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget ufjfmltk::core ufjfmltk::classifier ufjfmltk::valid ufjfmltk::clusterer ufjfmltk::ensemble ufjfmltk::featselect ufjfmltk::regressor ufjfmltk::visual ufjfmltk::ufjfmltk)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Create imported target ufjfmltk::core
add_library(ufjfmltk::core STATIC IMPORTED)

set_target_properties(ufjfmltk::core PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-core/include"
)

# Create imported target ufjfmltk::classifier
add_library(ufjfmltk::classifier STATIC IMPORTED)

set_target_properties(ufjfmltk::classifier PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-classifier/include"
  INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:ufjfmltk::core>"
)

# Create imported target ufjfmltk::valid
add_library(ufjfmltk::valid INTERFACE IMPORTED)

set_target_properties(ufjfmltk::valid PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-valid/include"
  INTERFACE_LINK_LIBRARIES "ufjfmltk::core;ufjfmltk::classifier"
)

# Create imported target ufjfmltk::clusterer
add_library(ufjfmltk::clusterer INTERFACE IMPORTED)

set_target_properties(ufjfmltk::clusterer PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-clusterer/include"
  INTERFACE_LINK_LIBRARIES "ufjfmltk::core"
)

# Create imported target ufjfmltk::ensemble
add_library(ufjfmltk::ensemble INTERFACE IMPORTED)

set_target_properties(ufjfmltk::ensemble PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-ensemble/include"
  INTERFACE_LINK_LIBRARIES "ufjfmltk::core;ufjfmltk::classifier;ufjfmltk::valid"
)

# Create imported target ufjfmltk::featselect
add_library(ufjfmltk::featselect INTERFACE IMPORTED)

set_target_properties(ufjfmltk::featselect PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-featselect/include"
  INTERFACE_LINK_LIBRARIES "ufjfmltk::core;ufjfmltk::classifier;ufjfmltk::valid"
)

# Create imported target ufjfmltk::regressor
add_library(ufjfmltk::regressor INTERFACE IMPORTED)

set_target_properties(ufjfmltk::regressor PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-regressor/include"
  INTERFACE_LINK_LIBRARIES "ufjfmltk::core"
)

# Create imported target ufjfmltk::visual
add_library(ufjfmltk::visual STATIC IMPORTED)

set_target_properties(ufjfmltk::visual PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/subprojects/ufjfmltk-visual/include"
  INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:ufjfmltk::core>;\$<LINK_ONLY:-lstdc++fs>"
)

# Create imported target ufjfmltk::ufjfmltk
add_library(ufjfmltk::ufjfmltk STATIC IMPORTED)

set_target_properties(ufjfmltk::ufjfmltk PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src/include"
  INTERFACE_LINK_LIBRARIES "ufjfmltk::regressor;ufjfmltk::ensemble;ufjfmltk::clusterer;ufjfmltk::featselect;ufjfmltk::valid;ufjfmltk::visual"
)

# Import target "ufjfmltk::core" for configuration "Debug"
set_property(TARGET ufjfmltk::core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ufjfmltk::core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/Debug/cored.lib"
  )

# Import target "ufjfmltk::classifier" for configuration "Debug"
set_property(TARGET ufjfmltk::classifier APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ufjfmltk::classifier PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/Debug/classifierd.lib"
  )

# Import target "ufjfmltk::visual" for configuration "Debug"
set_property(TARGET ufjfmltk::visual APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ufjfmltk::visual PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/Debug/visuald.lib"
  )

# Import target "ufjfmltk::ufjfmltk" for configuration "Debug"
set_property(TARGET ufjfmltk::ufjfmltk APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ufjfmltk::ufjfmltk PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/Debug/ufjfmltkd.lib"
  )

# Import target "ufjfmltk::core" for configuration "Release"
set_property(TARGET ufjfmltk::core APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ufjfmltk::core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/Release/core.lib"
  )

# Import target "ufjfmltk::classifier" for configuration "Release"
set_property(TARGET ufjfmltk::classifier APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ufjfmltk::classifier PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/Release/classifier.lib"
  )

# Import target "ufjfmltk::visual" for configuration "Release"
set_property(TARGET ufjfmltk::visual APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ufjfmltk::visual PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/Release/visual.lib"
  )

# Import target "ufjfmltk::ufjfmltk" for configuration "Release"
set_property(TARGET ufjfmltk::ufjfmltk APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ufjfmltk::ufjfmltk PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/Release/ufjfmltk.lib"
  )

# Import target "ufjfmltk::core" for configuration "MinSizeRel"
set_property(TARGET ufjfmltk::core APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(ufjfmltk::core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/MinSizeRel/core.lib"
  )

# Import target "ufjfmltk::classifier" for configuration "MinSizeRel"
set_property(TARGET ufjfmltk::classifier APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(ufjfmltk::classifier PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/MinSizeRel/classifier.lib"
  )

# Import target "ufjfmltk::visual" for configuration "MinSizeRel"
set_property(TARGET ufjfmltk::visual APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(ufjfmltk::visual PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/MinSizeRel/visual.lib"
  )

# Import target "ufjfmltk::ufjfmltk" for configuration "MinSizeRel"
set_property(TARGET ufjfmltk::ufjfmltk APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(ufjfmltk::ufjfmltk PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/MinSizeRel/ufjfmltk.lib"
  )

# Import target "ufjfmltk::core" for configuration "RelWithDebInfo"
set_property(TARGET ufjfmltk::core APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(ufjfmltk::core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/RelWithDebInfo/core.lib"
  )

# Import target "ufjfmltk::classifier" for configuration "RelWithDebInfo"
set_property(TARGET ufjfmltk::classifier APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(ufjfmltk::classifier PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/RelWithDebInfo/classifier.lib"
  )

# Import target "ufjfmltk::visual" for configuration "RelWithDebInfo"
set_property(TARGET ufjfmltk::visual APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(ufjfmltk::visual PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/RelWithDebInfo/visual.lib"
  )

# Import target "ufjfmltk::ufjfmltk" for configuration "RelWithDebInfo"
set_property(TARGET ufjfmltk::ufjfmltk APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(ufjfmltk::ufjfmltk PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "C:/Users/Marim/source/repos/ufjfmltk-cli/build/lib/RelWithDebInfo/ufjfmltk.lib"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
