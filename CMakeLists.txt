cmake_minimum_required(VERSION 3.1)
project(minicalc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include/)

add_library(lexer src/lexer.cpp)
add_library(parser src/parser.cpp)

add_executable(minicalc src/main.cpp)
target_link_libraries(minicalc lexer parser)
