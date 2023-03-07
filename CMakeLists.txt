cmake_minimum_required(VERSION 3.18)
project(GSCrossPlatform)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARY_NAME  ${PROJECT_NAME}Library)
set(PROJECT_DIR   ${CMAKE_SOURCE_DIR})
set(INCLUDE_DIR   ${PROJECT_DIR}/include)
set(SOURCE_DIR    ${PROJECT_DIR}/src)
set(BINARY_DIR    ${CMAKE_BINARY_DIR})
set(INSTALL_DIR   ${CMAKE_INSTALL_PREFIX})

message(STATUS "GSCrossPlatform")
message(STATUS "    LibraryName:  ${LIBRARY_NAME}")
message(STATUS "    ProjectDir:   ${PROJECT_DIR}")
message(STATUS "    IncludeDir:   ${INCLUDE_DIR}")
message(STATUS "    SourceDir:    ${SOURCE_DIR}")
message(STATUS "    BinaryDir:    ${BINARY_DIR}")
message(STATUS "    InstallDir:   ${INSTALL_DIR}")

find_package(ICU REQUIRED)

add_library(${LIBRARY_NAME}
        ${SOURCE_DIR}/UString.cpp
        ${SOURCE_DIR}/IO.cpp)

include_directories(${ICU_INCLUDE_DIRS})

include_directories(${INCLUDE_DIR})

install(DIRECTORY "include" DESTINATION ${INSTALL_DIR})

install(TARGETS ${LIBRARY_NAME} DESTINATION ${INSTALL_DIR}/lib)
