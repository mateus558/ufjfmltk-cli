set(WIDGETS_TARGET widgets)

set(WIDGETS_SRC
        src/DatasetWidget.cpp
        src/ArtificialDataWidget.cpp
        src/DataWidget.cpp
        src/VisualizationWidget.cpp
        src/ClassifiersWidget.cpp
        src/FeatSelectWidget.cpp
        src/RegressorWidget.cpp
        src/ClustererWidget.cpp
        src/ValidationWidget.cpp
        src/MLTKApp.cpp
        )
set(WIDGETS_HDR
        include/ArtificialDataWidget.h
        include/DatasetWidget.h
        include/DataWidget.h
        include/ClassifiersWidget.h
        include/RegressorWidget.h
        include/FeatSelectWidget.h
        include/VisualizationWidget.h
        include/ClustererWidget.h
        include/ValidationWidget.h
        include/MLTKApp.h
        include/settings.h
        )


add_library(${WIDGETS_TARGET} ${WIDGETS_SRC} ${WIDGETS_HDR})

set_target_properties(${WIDGETS_TARGET}  PROPERTIES
        PUBLIC_HEADER "${WIDGETS_HDR}")

target_include_directories(${WIDGETS_TARGET} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")


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