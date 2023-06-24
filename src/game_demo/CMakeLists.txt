project(game_demo)

set(WORLD_OBJECTS ./world_objects)
include_directories(${WORLD_OBJECTS})

set(
        WORLD_OBJECTS
        ${WORLD_OBJECTS}/game_object.h
        ${WORLD_OBJECTS}/ball.h
        ${WORLD_OBJECTS}/ball.cpp
        ${WORLD_OBJECTS}/spring.h
        ${WORLD_OBJECTS}/spring.cpp
        simulation_renderer.h
        simulation_renderer.cpp
        world.h
        world.cpp)

## executable with enabled export
add_executable(game_demo ${WORLD_OBJECTS})