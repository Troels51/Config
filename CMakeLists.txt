cmake_minimum_required(VERSION 2.8)

project (Config)
set(CMAKE_BUILD_TYPE Release)

set(SOURCES 
    src/Config.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Config SHARED ${SOURCES})

