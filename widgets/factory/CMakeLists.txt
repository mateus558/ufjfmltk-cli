set(FACTORY_TARGET factory)

set(FACTORY_SRC
        src/ClassifiersFactory.cpp
        src/ClusterersFactory.cpp
        src/FeatSelectFactory.cpp
        src/RegressorsFactory.cpp
        )
set(FACTORY_HDR
        include/ClassifiersFactory.h
        include/ClusterersFactory.h
        include/RegressorsFactory.h
        include/FeatSelectFactory.h
        )


add_library(${FACTORY_TARGET} ${FACTORY_SRC} ${FACTORY_HDR})

set_target_properties(${FACTORY_TARGET}  PROPERTIES
        PUBLIC_HEADER "${FACTORY_HDR}")

target_include_directories(${FACTORY_TARGET} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")

target_link_libraries(${FACTORY_TARGET} PRIVATE ufjfmltk cppcli)

install(TARGETS ${FACTORY_TARGET}
        EXPORT  ${PROJECT_NAME}
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" COMPONENT dev)

message(STATUS "Created target ${FACTORY_TARGET} for export ${PROJECT_NAME}.")