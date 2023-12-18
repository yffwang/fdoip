set(TARGET_EXECUTABLE example_target)

add_executable(${TARGET_EXECUTABLE}
        ${CMAKE_CURRENT_LIST_DIR}/example_coroutine1.cpp
)

target_include_directories(${TARGET_EXECUTABLE}
    PRIVATE
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${TARGET_EXECUTABLE}
    PRIVATE
        ${Boost_LIBRARIES}
        pthread
)

install(TARGETS ${TARGET_EXECUTABLE} DESTINATION ${PROJ_BIN_DIR}/test)

