cmake_minimum_required(VERSION 3.24)
project(simple_physics_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENGINE_HEADERS ./include)
set(ENGINE_SOURCE ./src)
set(SFML_DIR ./home/dave/SFML-2.5.1/include/SFML)
set(GAME_DEMO ./src/game_demo)
set(WORLD_OBJECTS ./src/game_demo/world_objects)

include_directories(${ENGINE_HEADERS})
include_directories(${ENGINE_SOURCE})
include_directories(${GAME_DEMO})
include_directories(${WORLD_OBJECTS})

set(
        ENGINE_FILES
        ${ENGINE_HEADERS}/engine/particle.h
        ${ENGINE_HEADERS}/engine/vector.h
        ${ENGINE_HEADERS}/engine/precision.h
        ${ENGINE_HEADERS}/engine/force_generator_abstract.h
        ${ENGINE_HEADERS}/engine/collision_detector.h
        ${ENGINE_HEADERS}/engine/collision_resolver.h
        ${ENGINE_SOURCE}/particle.cpp
        ${ENGINE_SOURCE}/collision_detector.cpp
        ${ENGINE_SOURCE}/collision_resolver.cpp
        ${ENGINE_SOURCE}/main.cpp)

set(
        GAME_DEMO_FILES
        ${WORLD_OBJECTS}/game_object.h
        ${WORLD_OBJECTS}/ball.h
        ${WORLD_OBJECTS}/ball.cpp
        ${WORLD_OBJECTS}/spring.h
        ${WORLD_OBJECTS}/spring.cpp
        ${WORLD_OBJECTS}/wall.h
        ${WORLD_OBJECTS}/wall.cpp
        ${GAME_DEMO}/simulation_renderer.h
        ${GAME_DEMO}/simulation_renderer.cpp
        ${GAME_DEMO}/world.h
        ${GAME_DEMO}/world.cpp)

## Google tests
add_subdirectory(tests)

add_executable(simple_physics_engine ${ENGINE_FILES} ${GAME_DEMO_FILES})
target_link_libraries(simple_physics_engine sfml-system sfml-window sfml-graphics)