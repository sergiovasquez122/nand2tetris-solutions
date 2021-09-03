cmake_minimum_required(VERSION 3.17)
project(07)

set(CMAKE_CXX_STANDARD 14)

add_executable(07 main.cpp Parser.cpp Parser.h CodeWriter.cpp CodeWriter.h)