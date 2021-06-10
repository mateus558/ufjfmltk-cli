set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR UFJF)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ufjfmltk CLI.")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_VERBATIM_VARIABLES YES)
if(WIN32)
    macro(prepareNSIS_Link linkName appName params)
     #prepare start menu links
     LIST(APPEND CPACK_NSIS_CREATE_ICONS_EXTRA "  CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${linkName}.lnk' '$INSTDIR\\\\bin\\\\${appName}.exe' '${params}'")
     LIST(APPEND CPACK_NSIS_DELETE_ICONS_EXTRA "  Delete '$SMPROGRAMS\\\\$START_MENU\\\\${linkName}.lnk'")

     #prepare desktop links
     LIST(APPEND CPACK_NSIS_CREATE_ICONS_EXTRA  "  CreateShortCut '$DESKTOP\\\\${linkName}.lnk' '$INSTDIR\\\\bin\\\\${appName}.exe' '${params}'")
     LIST(APPEND CPACK_NSIS_DELETE_ICONS_EXTRA  "  Delete '$DESKTOP\\\\${linkName}.lnk'")
    endmacro()
    set(CPACK_CREATE_DESKTOP_LINKS "ufjfmltk")
    set(CPACK_PACKAGING_INSTALL_PREFIX "")
    set(CPACK_NSIS_PACKAGE_NAME "${PROJECT_NAME}")
    set(CPACK_NSIS_DISPLAY_NAME "${PROJECT_NAME}")
    set(CPACK_NSIS_CONTACT "mateus.marim@ice.ufjf.br")
    set(CPACK_CREATE_DESKTOP_LINKS "${PROJECT_NAME}")
    PREPARENSIS_LINK("UFJF - Machine Learning Toolkit" "ufjfmltk-cli" "")
    string (REPLACE ";" "\n" CPACK_NSIS_CREATE_ICONS_EXTRA "${CPACK_NSIS_CREATE_ICONS_EXTRA}")
    string (REPLACE ";" "\n" CPACK_NSIS_DELETE_ICONS_EXTRA "${CPACK_NSIS_DELETE_ICONS_EXTRA}")
# Icon in the add/remove control panel. Must be an .exe file 
    set(CPACK_NSIS_INSTALLED_ICON_NAME bin\\\\${PROJECT_NAME}.exe)

    set(CPACK_NSIS_MODIFY_PATH ON)
    set(CPACK_GENERATOR ZIP NSIS)
elseif(APPLE)
    set(CPACK_GENERATOR TGZ productbuild)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CPACK_GENERATOR RPM DEB IFW)
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/mateus558/ufjfmltk-cli")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Mateus Coutinho Marim")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "gnuplot, gnuplot-x11")
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
else()
    set(CPACK_GENERATOR TGZ)
endif()
set(CPACK_SOURCE_IGNORE_FILES
        /\\.git/
        "/cmake-build-debug/"
        "/cmake-build-release/"
        "/cmake-build-test/"
        "/cmake-build-debug-coverage/"
        "/build/"
        "/builddir/"
        "/debug/"
        "/release/"
        "/wraps/"
        "/.idea/"
        "/.github/"
        "/.vscode/"
        "/docs/"
        "/tests/"
        "/datasets/"
        "../packaging/"
        )

include(CPack)