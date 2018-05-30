cmake_minimum_required(VERSION 3.10)
project(Kryzys)

set(CMAKE_CXX_STANDARD 17)

add_executable(Kryzys main.cpp fiber.h Graph.cpp Graph.h)