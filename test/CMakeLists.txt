cmake_minimum_required(VERSION 3.18)
project(GSCrossPlatformTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})

find_package(GSCrossPlatform REQUIRED)

find_package(GTest REQUIRED)

find_package(ICU REQUIRED)

if (${MSVC})
    add_compile_options(/utf-8)
endif()

set(PROJECT_INCLUDE_DIRS ${GSCrossPlatform_INCLUDE_DIRS} ${GTest_INCLUDE_DIRS} ${ICU_INCLUDE_DIRS})

set(PROJECT_LIB_DIRS ${GSCrossPlatform_LIB_DIRS} ${GTest_LIB_DIRS} ${ICU_LIB_DIRS})

set(PROJECT_LIBS ${GSCrossPlatform_LIBS} ${GTest_LIBS} ${ICU_LIBS})

add_executable(GSCrossPlatformStringTests GS_CrossPlatformStringTests.cpp)

target_include_directories(GSCrossPlatformStringTests PRIVATE ${PROJECT_INCLUDE_DIRS})

target_link_directories(GSCrossPlatformStringTests PRIVATE ${PROJECT_LIB_DIRS})

target_link_libraries(GSCrossPlatformStringTests PRIVATE ${PROJECT_LIBS})
