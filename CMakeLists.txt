cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_CLANG_TIDY
    clang-tidy
)

project(
    itsaunit
    VERSION 0.1.0
    LANGUAGES CXX
)
set(C_STANDARD C14)

add_library(itsaunit INTERFACE)
target_include_directories(itsaunit INTERFACE include)

add_subdirectory(test)
