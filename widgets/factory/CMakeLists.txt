set(FACTORY_TARGET factory)

set(FACTORY_SRC
        ClassifiersFactory.cpp
        )
set(FACTORY_HDR
        ClassifiersFactory.h
        )


add_library(${FACTORY_TARGET} STATIC ${FACTORY_SRC} ${FACTORY_HDR})

set_target_properties(${FACTORY_TARGET}  PROPERTIES
        PUBLIC_HEADER "${FACTORY_HDR}")

target_link_libraries(${FACTORY_TARGET} PRIVATE ufjfmltk cppcli)

install(TARGETS ${FACTORY_TARGET}
        EXPORT  ${PROJECT_NAME}
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" COMPONENT dev)

message(STATUS "Created target ${FACTORY_TARGET} for export ${PROJECT_NAME}.")