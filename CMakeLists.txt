cmake_minimum_required(VERSION 3.10.0)
project(MyString VERSION 0.1.0 LANGUAGES C CXX)

add_executable(MyString mystring.cpp test.cpp)

set_property(TARGET MyString PROPERTY CXX_STANDARD 23)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build.")
endif()

target_compile_options(MyString PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Debug>:-O0>
)

target_compile_options(MyString PRIVATE
    -Wall
    -Wextra
)