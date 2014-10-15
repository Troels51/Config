cmake_minimum_required(VERSION 2.8)

project (Config)
set(CMAKE_BUILD_TYPE Release)

set(SOURCES 
    src/Config.cpp
)
SET(CMAKE_CXX_FLAGS "-std=c++0x")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_NAMESPACE "")
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Config SHARED ${SOURCES})
enable_testing()

file(COPY test/jsontest.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Test test/test.cpp)
