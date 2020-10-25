cmake_minimum_required(VERSION 3.14)

project(gba-tileeditor
    LANGUAGES CXX
    DESCRIPTION "A Gameboy Advance tile editor"
)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pedantic -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pedantic -g3 -O0")

if (CMAKE_BUILD_TYPE)
    message(STATUS "Build type set to " ${CMAKE_BUILD_TYPE})
endif()

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Otherwise headers are not processed by AUTOMOC
cmake_policy(SET CMP0100 NEW)

add_subdirectory(gba-tileeditor-client)
