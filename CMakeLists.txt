cmake_minimum_required(VERSION 3.24)
project(simple_physics_engine)

set(CMAKE_CXX_STANDARD 20)

set(ENGINE_HEADERS ./include)
set(ENGINE_SOURCE ./src)

set(SFML_DIR ./home/dave/SFML-2.5.1/include/SFML)

include_directories(${ENGINE_HEADERS})
include_directories(${ENGINE_SOURCE})

set(
        SOURCE_FILES
        ${ENGINE_HEADERS}/engine/particle.h
        ${ENGINE_HEADERS}/engine/vector.h
        ${ENGINE_HEADERS}/engine/precision.h
        ${ENGINE_HEADERS}/engine/force_generator_abstract.h
        ${ENGINE_SOURCE}/particle.cpp
        ${ENGINE_SOURCE}/main.cpp
        ${ENGINE_SOURCE}/demo_spring.cpp
        ${ENGINE_SOURCE}/ball.h
        ${ENGINE_SOURCE}/ball.cpp
        ${ENGINE_SOURCE}/spring.h
        ${ENGINE_SOURCE}/spring.cpp)

add_executable(simple_physics_engine ${SOURCE_FILES})
target_link_libraries(simple_physics_engine sfml-system sfml-window sfml-graphics)