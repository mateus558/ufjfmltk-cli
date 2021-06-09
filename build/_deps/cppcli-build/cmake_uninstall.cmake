if(NOT EXISTS "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/cppcli-build/install_manifest.txt")
    message(WARNING "Cannot find install manifest: \"C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/cppcli-build/install_manifest.txt\"")
    return()
endif()

file(READ "C:/Users/Marim/source/repos/ufjfmltk-cli/build/_deps/cppcli-build/install_manifest.txt" files)
string(STRIP "${files}" files)
string(REGEX REPLACE "\n" ";" files "${files}")
list(REVERSE files)
foreach(file ${files})
    message(STATUS "Uninstalling: $ENV{DESTDIR}${file}")
    if(EXISTS "$ENV{DESTDIR}${file}")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E remove "$ENV{DESTDIR}${file}"
            OUTPUT_VARIABLE rm_out
            RESULT_VARIABLE rm_retval)
        if(NOT "${rm_retval}" EQUAL 0)
            message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
        endif()
    else()
        message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
    endif()
endforeach(file)
