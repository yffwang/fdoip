set(SOFTWARE_COMPONENT_NAME         fdoip_client)
set(LIBRARY_VERSION                 1.0.0)

add_library(${SOFTWARE_COMPONENT_NAME} STATIC)

set_target_properties(${SOFTWARE_COMPONENT_NAME} PROPERTIES
    VERSION         ${LIBRARY_VERSION}
    SOVERSION       ${LIBRARY_VERSION}
)

add_subdirectory(../common common)

target_include_directories(${SOFTWARE_COMPONENT_NAME}
    PRIVATE
        ${LIBRARY_ROOT_DIR}/common/include
        ${Boost_INCLUDE_DIRS}
    # PUBLIC
    #     ${PROJ_ROOT}/public
)

target_link_libraries(${SOFTWARE_COMPONENT_NAME}
    PRIVATE
        ${Boost_LIBRARIES}
        pthread
)

install(TARGETS ${SOFTWARE_COMPONENT_NAME}
    LIBRARY DESTINATION ${PROJ_BIN_DIR}/lib
    ARCHIVE DESTINATION ${PROJ_BIN_DIR}/lib
    RUNTIME DESTINATION ${PROJ_BIN_DIR}/bin
)

# install(FILES mylibrary.h
#     DESTINATION include
# )


