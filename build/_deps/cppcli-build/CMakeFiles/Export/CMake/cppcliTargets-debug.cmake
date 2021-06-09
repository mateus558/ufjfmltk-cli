#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cppcli::cppcli" for configuration "Debug"
set_property(TARGET cppcli::cppcli APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(cppcli::cppcli PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/cppclid.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS cppcli::cppcli )
list(APPEND _IMPORT_CHECK_FILES_FOR_cppcli::cppcli "${_IMPORT_PREFIX}/lib/cppclid.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
