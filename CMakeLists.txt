cmake_minimum_required(VERSION 3.18)
project(GSCrossPlatform)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARY_NAME ${PROJECT_NAME}Library)
set(PROJECT_DIR  ${PROJECT_SOURCE_DIR})
set(INCLUDE_DIR  ${PROJECT_DIR}/include)
set(SOURCE_DIR   ${PROJECT_DIR}/src)
set(BINARY_DIR   ${PROJECT_BINARY_DIR})

message(STATUS "GSCrossPlatform")
message(STATUS "    LibraryName: ${LIBRARY_NAME}")
message(STATUS "    ProjectDir:  ${PROJECT_DIR}")
message(STATUS "    IncludeDir:  ${INCLUDE_DIR}")
message(STATUS "    SourceDir:   ${SOURCE_DIR}")
message(STATUS "    BinaryDir:   ${BINARY_DIR}")

set(PROJECT_INCLUDES ${INCLUDE_DIR})

add_library(${LIBRARY_NAME}
        ${SOURCE_DIR}/GS_CrossPlatformString.cpp
        ${SOURCE_DIR}/GS_CrossPlatformIO.cpp)

target_include_directories(${LIBRARY_NAME} PRIVATE ${PROJECT_INCLUDES})
