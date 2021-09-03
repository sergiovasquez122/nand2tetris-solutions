cmake_minimum_required(VERSION 3.17)
project(08)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

add_executable(08 main.cpp Parser.cpp Parser.h CodeWriter.cpp CodeWriter.h)