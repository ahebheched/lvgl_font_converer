cmake_minimum_required(VERSION 3.30)
project(showfontimg)

set(CMAKE_CXX_STANDARD 20)

add_executable(showfontimg main.cpp)

target_include_directories(showfontimg PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

FILE(GLOB app_sources *.cpp)

target_sources(showfontimg PRIVATE
    ${app_sources}
)
