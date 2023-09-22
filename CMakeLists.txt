cmake_minimum_required(VERSION 3.16)
project(fdoip VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PROJ_ROOT_DIR   ${CMAKE_CURRENT_LIST_DIR})
set(PROJ_BIN_DIR    ${CMAKE_CURRENT_LIST_DIR}/bin)

message(STATUS ">>>> --------------------------------------")
message(STATUS ">>>> PROJECT: ${PROJECT_NAME}")
message(STATUS ">>>> --------------------------------------")
message(STATUS ">>>> CMAKE_C_COMPILER:      ${CMAKE_C_COMPILER}")
message(STATUS ">>>> CMAKE_CXX_COMPILER:    ${CMAKE_CXX_COMPILER}")
message(STATUS ">>>> CMAKE_AR:              ${CMAKE_AR}")
message(STATUS ">>>> CMAKE_RANLIB:          ${CMAKE_RANLIB}")
message(STATUS ">>>> CMAKE_LINKER:          ${CMAKE_LINKER}")
message(STATUS ">>>> --------------------------------------")
message(STATUS ">>>> CMAKE_MINIMUM_REQUIRED_VERSION:    ${CMAKE_MINIMUM_REQUIRED_VERSION}")
message(STATUS ">>>> CMAKE_VERSION:                     ${CMAKE_VERSION}")
message(STATUS ">>>> --------------------------------------")
message(STATUS ">>>> --------------------------------------")

find_package(Boost REQUIRED COMPONENTS)
message(STATUS ">>>> Boost_INCLUDE_DIR:     ${Boost_INCLUDE_DIRS}")
message(STATUS ">>>> Boost_LIB_DIR:         ${Boost_LIBRARIES}")

add_subdirectory(test)
