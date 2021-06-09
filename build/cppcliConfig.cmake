set(cppcli_VERSION 1.0.0)


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was cppcliConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

####################################################################################



if(NOT TARGET cppcli::cppcli)
  include("${CMAKE_CURRENT_LIST_DIR}/cppcliTargets.cmake")
endif()

# Compatibility
get_property(cppcli_cppcli_INCLUDE_DIR TARGET cppcli::cppcli PROPERTY INTERFACE_INCLUDE_DIRECTORIES)

set(cppcli_LIBRARIES cppcli::cppcli)
set(cppcli_INCLUDE_DIRS "${cppcli_cppcli_INCLUDE_DIR}")
list(REMOVE_DUPLICATES cppcli_INCLUDE_DIRS)


