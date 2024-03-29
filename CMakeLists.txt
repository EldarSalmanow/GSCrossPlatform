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

set(EXTERNAL_INCLUDE_DIRS )
set(EXTERNAL_LIBS         )

# ICU

find_package(ICU REQUIRED)

set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${ICU_INCLUDE_DIRS})
set(EXTERNAL_LIBS         ${EXTERNAL_LIBS}         ${ICU_LIBRARIES})

add_library(${LIBRARY_NAME}
        ${SOURCE_DIR}/UString.cpp
        ${SOURCE_DIR}/IO.cpp)

target_include_directories(${LIBRARY_NAME} PRIVATE ${EXTERNAL_INCLUDE_DIRS})

target_include_directories(${LIBRARY_NAME} PRIVATE ${INCLUDE_DIR})

target_link_libraries(${LIBRARY_NAME} PRIVATE ${EXTERNAL_LIBS})

install(DIRECTORY "include" DESTINATION ${INSTALL_DIR})

install(TARGETS ${LIBRARY_NAME} DESTINATION ${INSTALL_DIR}/lib)
