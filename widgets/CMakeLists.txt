set(WIDGETS_TARGET widgets)

set(WIDGETS_SRC
        DatasetWidget.cpp
        DataWidget.cpp
        VisualizationWidget.cpp
        ClassifiersWidget.cpp
        FeatSelectWidget.cpp
        RegressorWidget.cpp
        ClustererWidget.cpp
        ValidationWidget.cpp
        MLTKApp.cpp
        )
set(WIDGETS_HDR
        DatasetWidget.h
        DataWidget.h
        ClassifiersWidget.h
        RegressorWidget.h
        FeatSelectWidget.h
        VisualizationWidget.h
        ClustererWidget.h
        ValidationWidget.h
        MLTKApp.h
        settings.h
        )


add_library(${WIDGETS_TARGET} STATIC ${WIDGETS_SRC} ${WIDGETS_HDR})

set_target_properties(${WIDGETS_TARGET}  PROPERTIES
        PUBLIC_HEADER "${WIDGETS_HDR}")

add_subdirectory(factory)

target_link_libraries(${WIDGETS_TARGET} PRIVATE factory)
target_link_libraries(${WIDGETS_TARGET} PUBLIC ufjfmltk cppcli)

install(TARGETS ${WIDGETS_TARGET}
        EXPORT  ${PROJECT_NAME}
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" COMPONENT dev)

message(STATUS "Created target ${WIDGETS_TARGET} for export ${PROJECT_NAME}.")