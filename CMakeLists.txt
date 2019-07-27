cmake_minimum_required(VERSION 3.13)
project(EventEmitter++)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE sources "src/*.cpp")

add_library(eepp ${sources})
target_compile_options(eepp PUBLIC -Wall)
target_include_directories(eepp PUBLIC "include")