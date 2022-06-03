cmake_minimum_required(VERSION 3.18)
project(GSCrossPlatform)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_DIR   ${CMAKE_SOURCE_DIR})
set(INCLUDE_DIR   ${PROJECT_DIR}/include)
set(BINARY_DIR    ${CMAKE_BINARY_DIR})
set(INSTALL_DIR   ${CMAKE_INSTALL_PREFIX})

message(STATUS "GSCrossPlatform")
message(STATUS "    ProjectDir:   ${PROJECT_DIR}")
message(STATUS "    IncludeDir:   ${INCLUDE_DIR}")
message(STATUS "    BinaryDir:    ${BINARY_DIR}")
message(STATUS "    InstallDir:   ${INSTALL_DIR}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${BINARY_DIR})

find_package(ICU REQUIRED)

set(PROJECT_INCLUDE_DIRS ${INCLUDE_DIR} ${ICU_INCLUDE_DIRS})

include_directories(${PROJECT_INCLUDE_DIRS})

install(DIRECTORY "include" DESTINATION ${INSTALL_DIR})
