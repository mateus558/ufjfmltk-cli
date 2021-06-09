# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.20.3)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(ufjfmltk-populate NONE)



include(ExternalProject)
ExternalProject_Add(ufjfmltk-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://github.com/mateus558/UFJF-Machine-Learning-Toolkit/archive/refs/tags/v0.51.1-beta.7.tar.gz"
                    SOURCE_DIR          "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-src"
                    BINARY_DIR          "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/ufjfmltk-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


