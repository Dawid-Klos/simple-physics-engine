cmake_minimum_required(VERSION 3.24)
project(simple_physics_engine)

set(CMAKE_CXX_STANDARD 20)

set(ENGINE_HEADERS ./include)
set(ENGINE_SOURCE ./src)

include_directories(${ENGINE_HEADERS})
include_directories(${ENGINE_SOURCE})

set(
        SOURCE_FILES
        ${ENGINE_HEADERS}/engine/particle.h
        ${ENGINE_HEADERS}/engine/vector.h
        ${ENGINE_HEADERS}/engine/precision.h
        ${ENGINE_SOURCE}/particle.cpp
        ${ENGINE_SOURCE}/main.cpp)

add_executable(simple_physics_engine ${SOURCE_FILES})