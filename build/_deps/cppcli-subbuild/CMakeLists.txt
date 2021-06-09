# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.20.3)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(cppcli-populate NONE)



include(ExternalProject)
ExternalProject_Add(cppcli-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://github.com/mateus558/cppcli/archive/refs/tags/v1.2.1.tar.gz"
                    SOURCE_DIR          "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/cppcli-src"
                    BINARY_DIR          "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/cppcli-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


