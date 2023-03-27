cmake_minimum_required(VERSION 3.24)
project(simple_physics_engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(simple_physics_engine src/main.cpp include/engine/precision.h)
